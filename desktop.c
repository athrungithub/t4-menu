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
desktop_info (char *file)
{
    GKeyFile *keyfile;

    keyfile = g_key_file_new ();
    g_key_file_load_from_file (keyfile, file, G_KEY_FILE_NONE, NULL);

    /* Hidden= true means that the .desktopfile should be completely ignored */
  if (g_key_file_get_boolean (keyfile, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_HIDDEN, NULL) ||
          g_key_file_get_boolean (keyfile,G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_NO_DISPLAY, NULL))
    {
      g_key_file_free (keyfile);
      return;
    }
    char *executable_name = g_key_file_get_string (keyfile, G_KEY_FILE_DESKTOP_GROUP,
            G_KEY_FILE_DESKTOP_KEY_EXEC, NULL);
    char *generic_name = g_key_file_get_string (keyfile, G_KEY_FILE_DESKTOP_GROUP,
            G_KEY_FILE_DESKTOP_KEY_GENERIC_NAME, NULL);
    char *name = g_key_file_get_string (keyfile, G_KEY_FILE_DESKTOP_GROUP,
            G_KEY_FILE_DESKTOP_KEY_NAME, NULL) ;
    printf ("%s (%s)\n", name, (generic_name != NULL)? generic_name : executable_name);
    if (executable_name != NULL)
        g_free (executable_name);
    if (generic_name != NULL)
        g_free (generic_name);
    if (name != NULL)
        g_free (name);

    g_key_file_free (keyfile);
    return ;
}

static void
recurse_dir (const char *dir)
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

int
main (int argc, char **argv)
{
    const char **dirs;
    int i;

    dirs = NULL;
    dirs = get_default_search_path ();
    print_desktop_dirs (dirs);

    for (i = 0; dirs[i] != NULL; i++)
    {
        recurse_dir (dirs[i]);
    }

    char *directories;

    for (i; i >= 0 ; i--)
    {
        directories = (char *) dirs[i];
        g_free (directories);
    }
    directories = (char *)dirs;
    g_free (directories);
    return 0;
}
