/*
 * Initial main.c file generated by Glade. Edit as required.
 * Glade will not overwrite this file.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "interface.h"
#include "support.h"

int
main (int argc, char *argv[])
{
  GtkWidget *se_connecter;
  GtkWidget *creer_un_compte;
  GtkWidget *Liste_des_citoyens;
  GtkWidget *modification;

#ifdef ENABLE_NLS
  bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
  textdomain (GETTEXT_PACKAGE);
#endif

  gtk_set_locale ();
  gtk_init (&argc, &argv);

  add_pixmap_directory (PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps");

  /*
   * The following code was added by Glade to create one of each component
   * (except popup menus), just so that you see something after building
   * the project. Delete any components that you don't want shown initially.
   */
  se_connecter = create_connexion();
  gtk_widget_show (se_connecter);
  creer_un_compte = create_creer_un_compte ();
  gtk_widget_show (creer_un_compte);
  Liste_des_citoyens = create_Liste_des_citoyens ();
  gtk_widget_show (Liste_des_citoyens);
  modification=create_modification();
  gtk_widget_show (modification);

  gtk_main ();
  return 0;
}

