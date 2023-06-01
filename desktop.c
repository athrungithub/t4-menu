#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <glib/gprintf.h>
#include <glib/gi18n.h>
#include "desktop.h"

#define udd_print(...) g_printerr (__VA_ARGS__)
#define udd_verbose_print(...) g_printerr (__VA_ARGS__)


const gchar *lang;
GList *desktop_list;

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

/*
 * void
 * print_desktop_dirs (const char **dirs)
 * {
 *   char *directories;
 *
 *   directories = g_strjoinv (", ", (char **) dirs);
 *   udd_verbose_print(_("Search path is now: [%s]\n"), directories);
 *   g_free (directories);
 * }
 */

void
desktop_info (gchar *file)
{
    g_autoptr (GKeyFile) keyfile;
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

    it->terminal = g_key_file_get_boolean (keyfile, G_KEY_FILE_DESKTOP_GROUP,
            G_KEY_FILE_DESKTOP_KEY_TERMINAL, NULL);

    it->exec = g_key_file_get_value (keyfile, G_KEY_FILE_DESKTOP_GROUP,
            G_KEY_FILE_DESKTOP_KEY_EXEC, NULL);

    it->generic_name = g_key_file_get_locale_string (keyfile, G_KEY_FILE_DESKTOP_GROUP,
            G_KEY_FILE_DESKTOP_KEY_GENERIC_NAME, lang, NULL);

    it->name = g_key_file_get_locale_string (keyfile, G_KEY_FILE_DESKTOP_GROUP,
            G_KEY_FILE_DESKTOP_KEY_NAME, lang, NULL);

    if (!it->name)
    {
        g_warning ("Unable read Desktop Item Name: %s\n", file);
    }

    for (i = 0; it->exec[i] != ' '; i++) {}
    it->exec_striped = g_strndup (it->exec, i);

   desktop_list= g_list_insert_sorted (desktop_list, it, compare);

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
desktop_get_exec (GList *l, const char *name)
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

const struct item*
desktop_get_item (GList *l, const char *name)
{
    GList *tmp;

    tmp = l;

    while (tmp != NULL)
    {
        struct item *it = tmp->data;
        if (!g_strcmp0 (it->name, name))
        {
            return (it);
        }
        tmp = tmp->next;
    }
    return (NULL); // error not found
}

void
desktop_free_list (void)
{
    g_list_free_full (desktop_list, list_item_destroy);
    return;
}

void
desktop_init_list (void)
{
    const char **dire;
    int i;

   desktop_list= NULL;

    lang = g_getenv ("LANG");

    dire = NULL;
    dire = get_default_search_path ();
    /* print_desktop_dirs (dirs); */

    for (i = 0; dire[i] != NULL; i++)
    {
        recurse_dir (dire[i]);
    }
    return;
}

#ifdef TEST
int
main (int argc, char **argv)
{
    desktop_init_list ();

    GList *l = desktop_list;

    while (l != NULL)
    {
        GList *next = l->next;
        struct item *it = l->data;
        printf ("%s (%s)\n", it->name, (it->generic_name != NULL)? it->generic_name : it->exec_striped);

        l = next;
    }

    udd_print(_("exec: %s\n"), desktop_get_exec (desktop_list, "Zathura"));

    desktop_free_list ();

    return 0;
}
#endif
