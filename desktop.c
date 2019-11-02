#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <glib.h>
#include <glib/gprintf.h>
#include <glib/gi18n.h>

#define udd_print(...) if (!quiet) g_printerr (__VA_ARGS__)
#define udd_verbose_print(...) if (!quiet && verbose) g_printerr (__VA_ARGS__)

static gboolean verbose = TRUE, quiet = FALSE;

struct item
{
    char *name;
    char *generic_name;
    char *exec;
    char *exec_striped;
    gboolean terminal;
};

GList *list;
const gchar *lang;

gint
compare (gconstpointer a, gconstpointer b)
{
    const struct item *ai = a;
    const struct item *bi = b;

    return (g_strcmp0 (ai->name, bi->name));
}

static const char **
get_default_search_path (void)
{
  static char **args = NULL;
  const char * const *data_dirs;
  int i;

  if (args != NULL)
    return (const char **) args;

  data_dirs = g_get_system_data_dirs ();

  for (i = 0; data_dirs[i] != NULL; i++);

  args = g_new (char *, i + 1);

  for (i = 0; data_dirs[i] != NULL; i++)
    args[i] = g_build_filename (data_dirs[i], "applications", NULL);

  args[i] = NULL;

  return (const char **) args;
}

void
print_desktop_dirs (const char **dirs)
{
  char *directories;

  directories = g_strjoinv (", ", (char **) dirs);
  udd_verbose_print(_("Search path is now: [%s]\n"), directories);
  g_free (directories);
}

void
desktop_info (gchar *file)
{
    GKeyFile *keyfile;
    struct item *it;
    int i;

    keyfile = g_key_file_new ();
    g_key_file_load_from_file (keyfile, file, G_KEY_FILE_KEEP_TRANSLATIONS, NULL);

    /* Hidden= true means that the .desktopfile should be completely ignored */
  if (g_key_file_get_boolean (keyfile, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_HIDDEN, NULL) ||
          g_key_file_get_boolean (keyfile,G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_NO_DISPLAY, NULL))
    {
      g_key_file_free (keyfile);
      return;
    }

    it = g_new (struct item, 1);

    it->exec = g_key_file_get_value (keyfile, G_KEY_FILE_DESKTOP_GROUP,
            G_KEY_FILE_DESKTOP_KEY_EXEC, NULL);

    it->generic_name = g_key_file_get_locale_string (keyfile, G_KEY_FILE_DESKTOP_GROUP,
            G_KEY_FILE_DESKTOP_KEY_GENERIC_NAME, lang, NULL);

    it->name = g_key_file_get_locale_string (keyfile, G_KEY_FILE_DESKTOP_GROUP,
            G_KEY_FILE_DESKTOP_KEY_NAME, lang, NULL) ;

    it->terminal = g_key_file_get_boolean (keyfile, G_KEY_FILE_DESKTOP_GROUP,
            G_KEY_FILE_DESKTOP_KEY_TERMINAL, NULL);

    for (i = 0; it->exec[i] != ' '; i++) {}
    it->exec_striped = g_strndup (it->exec, i);

    list = g_list_insert_sorted (list, it, compare);

    g_key_file_free (keyfile);

    return ;
}

static void
recurse_dir (const gchar *dir)
{
  GDir *gdir;
  const char *filename;

  gdir = g_dir_open (dir, 0, NULL);

  while ((filename = g_dir_read_name (gdir)) != NULL)
  {
      char *full_path;

      full_path = g_build_filename (dir, filename, NULL);

      if (!g_str_has_suffix (filename, ".desktop"))
      {
          g_free (full_path);
          continue;
      }

      desktop_info (full_path);

      g_free (full_path);
  }
  g_dir_close (gdir);
}

void
list_item_destroy (gpointer data)
{
    struct item *i = (struct item*)data;

    if (i->name != NULL)
        g_free (i->name);
    if (i->generic_name != NULL)
        g_free (i->generic_name);
    if (i->exec != NULL)
        g_free (i->exec);
    if (i->exec_striped != NULL)
        g_free (i->exec_striped);
    g_free (i);
    return;
}

const char *
get_exec (GList *l, const char *name)
{
    /* g_list_foreach (l, get_exec_cb, name); */
    GList *tmp;

    tmp = l;
    while (tmp != NULL)
    {
        struct item *it = tmp->data;
        if (!g_strcmp0 (it->name, name))
        {
            return (it->exec);
        }
        tmp = tmp->next;
    }
    return (NULL); //error
}

int
main (int argc, char **argv)
{
    const char **dirs;
    int i;

    list = NULL;

    lang = g_getenv ("LANG");

    dirs = NULL;
    dirs = get_default_search_path ();
    /* print_desktop_dirs (dirs); */

    for (i = 0; dirs[i] != NULL; i++)
    {
        recurse_dir (dirs[i]);
    }

    GList *l = list;

    while (l != NULL)
    {
        GList *next = l->next;
        struct item *it = l->data;
        printf ("%s (%s)\n", it->name, (it->generic_name != NULL)? it->generic_name : it->exec_striped);

        l = next;
    }

    udd_print(_("exec: %s\n"), get_exec (list, "Zathura"));

    char *d;
    for (i; i >= 0 ; i--)
    {
        d = (char *) dirs[i];
        g_free (d);
    }

    d = (char *)dirs;
    g_free (d);

    g_list_free_full (list, list_item_destroy);

    return 0;
}
