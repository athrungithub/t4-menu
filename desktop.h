#include <glib.h>

#ifndef DESKTOP_H
#define DESKTOP_H

extern GList *desktop_list;

struct item
{
    char *name;
    char *generic_name;
    char *exec;
    char *exec_striped;
    gboolean terminal;
};

const char * desktop_get_exec (GList *l, const char *name);
void desktop_free_list (void);
void desktop_init_list (void);
const struct item * desktop_get_item (GList *l, const char *name);

#endif
