#include "include/cef_app.h"
#include "example.hpp"

#include <gtk/gtk.h>

CefRefPtr<ExampleHandler> g_handler;
CefRefPtr<CefRequestContextHandler> context_handler;

void
destroy(void) {
  CefQuitMessageLoop();
}

int
main(int argc, char **argv) {
  CefRefPtr<CefRequestContext> context = CefRequestContext::CreateContext(context_handler);
  CefMainArgs main_args(argc, argv);

  int exitCode = CefExecuteProcess(main_args, NULL, NULL);
  if (exitCode >= 0)
    return exitCode;

  CefSettings settings;
  CefInitialize(main_args, settings, NULL, NULL);

  GtkWidget *window;
  GtkWidget *vbox;
  GtkWidget *hbox;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "CEF3 Bare Bones Cross-Platorm Example");
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  vbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window), vbox);
  hbox = gtk_hbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);
  g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);
  CefBrowserSettings browserSettings;
  CefWindowInfo info;
  g_handler = new ExampleHandler();

  info.SetAsChild(hbox);
  CefBrowserHost::CreateBrowserSync(info, g_handler.get(), "http://www.github.com", browserSettings, context);

  gtk_widget_show_all(window);
  CefRunMessageLoop();
  CefShutdown();
  return 0;
}
