#include <gtk/gtk.h>
#include <glib/gprintf.h>
#include <stdlib.h>
#include <gdk/gdkkeysyms.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include "bc.h"
#include "bt.h"
#include "btree.h"
#include "btree_int.h"
#include<stdlib.h>
#define MEAN_LTH 20000
////////////////////////////////////////////
typedef struct info
{
  char word[100];
  char mean[MEAN_LTH];
}info;
char chr(int i);
int auto_complete(char *word,info *out);

//**************************************************************************
BTA *bt;
FILE *f;
char word[100],mean[MEAN_LTH];
char word1[100],mean1[MEAN_LTH];
char st[100],s[5],ch;
int rsize,i;
info out[70];
//**************************************************************************
typedef struct{
	GtkWidget *window1;
	GtkWidget *entry2;
	GtkWidget *textview1;
	GtkWidget *button1;
	GtkWidget *sua;
	GtkWidget *xoa;
	GtkWidget *them;
	GtkWidget *label1;
	GtkWidget *treeview1;
	GtkListStore *store;
} AppWidgets;
//************************************************************************
void add(BTA* bt,char *word,char *mean)
{
  btins(bt,word,mean,MEAN_LTH);
}
void delete(BTA* bt,char *word)
{
  btdel(bt,word);
}
//************************************************************************
void help_about(GtkWidget    *widget);
void on_open_activate(GtkWidget    *widget, AppWidgets *app);
void on_them_activate(GtkWidget    *widget, AppWidgets *app);
void on_xoa_activate(GtkWidget    *widget, AppWidgets *app);
void on_sua_activate(GtkWidget    *widget, AppWidgets *app);
char *soundex(const char *word);
int bt_soundex(char *word,info *out);
void on_button1_clicked(GtkButton *button, AppWidgets *app);
void on_button2_clicked(GtkWidget    *widget);
void on_button3_clicked(GtkButton *button, AppWidgets *app);
void on_them_clicked(GtkButton *button, AppWidgets *app);
void on_xoa_clicked(GtkButton *button, AppWidgets *app);
void on_sua_clicked(GtkButton *button, AppWidgets *app);

gboolean on_entry2_key_press_event(GtkWidget    *widget,    GdkEventKey   *event,   AppWidgets *app);
gboolean on_entry2_key_release_event(GtkWidget    *widget,    GdkEventKey   *event,   AppWidgets *app);

void on_treeview1_row_activated(GtkTreeView       *tree_view,
                                GtkTreePath       *path,
                                GtkTreeViewColumn *column,
                                AppWidgets *app);
int   main (int argc, char *argv[])
{
    GtkBuilder      *builder; 
    AppWidgets *app = g_slice_new(AppWidgets);
                                                bt=btopn("dictionary",0,1);
    gtk_init (&argc, &argv);
    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "tudien.glade", NULL);
//Goi cac entry den app.
#define appGET(xx) \
app->xx=GTK_WIDGET(gtk_builder_get_object(builder,#xx))
	appGET(entry2);
	appGET(textview1);
	appGET(button1);
	appGET(them);
	appGET(xoa);
	appGET(sua);
	appGET(label1);
	appGET(treeview1);
	appGET(window1);
//------------------------------------------------------------------------
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
renderer = gtk_cell_renderer_text_new ();
column = gtk_tree_view_column_new_with_attributes("SUGGEST", renderer, "text", 0, NULL);
gtk_tree_view_append_column (GTK_TREE_VIEW (app->treeview1), column);
app->store = gtk_list_store_new(1,G_TYPE_STRING);
gtk_tree_view_set_model(GTK_TREE_VIEW(app->treeview1),GTK_TREE_MODEL(app->store));

for( i = 0; i < auto_complete("",out); i++ )
   {
      GtkTreeIter iter;
      gtk_list_store_append( app->store, &iter );
      gtk_list_store_set( app->store, &iter, 0,out[i].word, -1 );
   }
//------------------------------------------------------------------------
    gtk_builder_connect_signals (builder, app);

    g_object_unref (G_OBJECT (builder));
        
    gtk_widget_show (app->window1);                
    gtk_main ();
    g_slice_free(AppWidgets,app);
                                                 btcls(bt);
    return 0;
}
///////////////////////////////////////////////////////////
char chr(int i)
{
  return ((0<=i) && (i<=9)) ? '0'+i : '-';
}
//////////////////////////////////////////////////////////
char *soundex(const char *word)
{
  static const char *lset[] = {
    "", "BFPVbfpv", "CGJKQSXZcgjkqsxz", "DTdt", "Ll","MNmn", "Rr"  };
#define LSIZE (sizeof(lset)/sizeof(char *))
  const char *ch;
  char *bp,*bufr;
  char prev = '-';
  int j;
  bufr=(char*)malloc(8*sizeof(char));
  bp = bufr;
  ch = word;  
  while (*ch && (bp-bufr<4)) {
    for (j=1; j< LSIZE; j++)
      if (strchr( lset[j], *ch) ) break;    
    if ((j<LSIZE) && (chr(j) != prev))
      *bp++ = prev = chr(j);
    else if (!strchr("WHwh", *ch)) 
      prev = '7';    
    if (ch == word) {
      bp = bufr;
      *bp++ = /*toupper(*ch)*/*ch-32;
    }
    ch++;
  }
  while (bp-bufr < 4)
    *bp++ = '0';
  *bp = 0;
  return bufr;
}
//**************************************************************************
int bt_soundex(char *word,info *out)
{
  int m,i=0,rsize;
  if(btsel(bt,word,mean,MEAN_LTH,&rsize)==0 )
    return -1;
  st[0]=word[0];
  st[1]='\0';
  bfndky(bt,st,&m);
  while(btseln(bt,word1,mean1,MEAN_LTH,&rsize)==0)
    {
      if(word1[0]!=st[0]) break;
      if(strcmp(soundex(word),soundex(word1))==0)
	{
	  strcpy(out[i].word,word1);
	  strcpy(out[i].mean,mean1);
	  i++;
	}
      if(i==20) break;
    }
  return i;
}

////////////////////////////////////////////////////////////////////////
int auto_complete(char *word,info *out)
{
  char st[50];
  int rsize,i=0;
  if(btsel(bt,word,mean,MEAN_LTH,&rsize)==0 )
    {
      strcpy(out[i].word,word);
      strcpy(out[i].mean,mean);
      i++;
    }
  while(btseln(bt,word1,mean1,MEAN_LTH,&rsize)==0)
    {
      strcpy(st,word1);
      st[strlen(word)]='\0';
      if(strcmp(st,word)==0) 
	{
	  strcpy(out[i].word,word1);
	  strcpy(out[i].mean,mean1);
	  i++;
	}
      else break;
      if(i==70) break;
    }
  return i;
}
///////////////////////////////////////////////////////////
void help_about(GtkWidget    *widget){
gtk_dialog_run(GTK_DIALOG(widget));
gtk_widget_hide(widget);
}
/////////////////////////////////////////////////////////////////////
void on_button1_clicked(GtkButton *button, AppWidgets *app)
{
const gchar *wordget = gtk_entry_get_text(GTK_ENTRY(app->entry2));
int p;
if((p=bt_soundex((char*)wordget,out))!=-1){
GtkWidget *view;
GtkTextBuffer *buf;
view = gtk_text_view_new ();
buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
gtk_text_buffer_set_text (buf,"Từ Này Không Tồn Tại !!!", -1);
 gtk_text_view_set_buffer(GTK_TEXT_VIEW(app->textview1),buf);

gtk_list_store_clear                (app->store);

   for( i = 0; i<p; i++ )
   {
      GtkTreeIter iter;
      gtk_list_store_append( app->store, &iter );
      gtk_list_store_set( app->store, &iter, 0,out[i].word, -1 );
   }
}
else{
GtkWidget *view;
GtkTextBuffer *buf;
view = gtk_text_view_new ();
buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
gtk_text_buffer_set_text (buf,out[0].mean, -1);
 gtk_text_view_set_buffer(GTK_TEXT_VIEW(app->textview1),buf);
}}

/////////////////////////////////////////////////////////////////////////
gboolean on_entry2_key_press_event(GtkWidget    *widget,    GdkEventKey   *event,   AppWidgets *app)
{
const gchar *wordget= gtk_entry_get_text(GTK_ENTRY(app->entry2));
if (event->keyval==GDK_Tab)
{
auto_complete((char*)wordget,out);
gtk_entry_set_text (GTK_ENTRY(app->entry2),out[0].word);
}
return 0;
}
//////////////////////////////////////////////////////////////////////////
gboolean on_entry2_key_release_event(GtkWidget    *widget,    GdkEventKey   *event,   AppWidgets *app)
{

const gchar *wordget= gtk_entry_get_text(GTK_ENTRY(app->entry2));

if(event->keyval==GDK_Return)
{ 
int p;
if((p=bt_soundex((char*)wordget,out))!=-1){
GtkWidget *view;
GtkTextBuffer *buf;
view = gtk_text_view_new ();
buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
gtk_text_buffer_set_text (buf,"Từ Này Không Tồn Tại !!!", -1);
 gtk_text_view_set_buffer(GTK_TEXT_VIEW(app->textview1),buf);

gtk_list_store_clear                (app->store);

   for( i = 0; i<p; i++ )
   {
      GtkTreeIter iter;
      gtk_list_store_append( app->store, &iter );
      gtk_list_store_set( app->store, &iter, 0,out[i].word, -1 );
   }
}
else{
GtkWidget *view;
GtkTextBuffer *buf;
view = gtk_text_view_new ();
buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
gtk_text_buffer_set_text (buf,out[0].mean, -1);
 gtk_text_view_set_buffer(GTK_TEXT_VIEW(app->textview1),buf);
}
}
else{
    gtk_list_store_clear                (app->store);
   for( i = 0; i < auto_complete((char*)wordget,out); i++ )
   {
      GtkTreeIter iter;
      gtk_list_store_append( app->store, &iter );
      gtk_list_store_set( app->store, &iter, 0,out[i].word, -1 );
   }
}
return 0;
}
/////////////////////////////////////////////////////////////////////
void on_treeview1_row_activated(GtkTreeView       *tree_view,
                                GtkTreePath       *path,
                                GtkTreeViewColumn *column,
                                AppWidgets *app               )
{
 GtkTreeModel *model;
 GtkTreeIter   iter;
model = gtk_tree_view_get_model(tree_view);
   if (gtk_tree_model_get_iter(model, &iter, path))
    {
       gchar *name;
       gtk_tree_model_get(model, &iter,0, &name, -1);
       gtk_entry_set_text (GTK_ENTRY(app->entry2),name);
       auto_complete((char*)name,out);
       GtkWidget *view;
       GtkTextBuffer *buf;
       view = gtk_text_view_new ();
       buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
       gtk_text_buffer_set_text (buf,out[0].mean, -1);
       gtk_text_view_set_buffer(GTK_TEXT_VIEW(app->textview1),buf);
       g_free(name);
    }
}
/////////////////////////////////////////////////////////////////////////
void on_open_activate(GtkWidget    *widget, AppWidgets *app){
GtkWidget *dialog;
dialog = gtk_file_chooser_dialog_new ("Open File",
				      NULL,
				      GTK_FILE_CHOOSER_ACTION_OPEN,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
				      NULL);
if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
  {
    char *filename;
    filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
     btcls(bt);
      bt=btopn(filename,0,1);
 gtk_list_store_clear(app->store);
	for( i = 0; i < auto_complete("",out); i++ )
   {
      GtkTreeIter iter;
      gtk_list_store_append( app->store, &iter );
      gtk_list_store_set( app->store, &iter, 0,out[i].word, -1 );
   }
	gtk_label_set_text(GTK_LABEL(app->label1),"File đã được mở");
    g_free (filename);
  }
gtk_widget_destroy (dialog);
}
//////////////////////////////////////////////////////////////////////////
void on_them_clicked(GtkButton *button, AppWidgets *app)
{
const gchar *wordget= gtk_entry_get_text(GTK_ENTRY(app->entry2));
if(strcmp(wordget,"")==0){
GtkWidget *dialog;
dialog = gtk_message_dialog_new (NULL,
                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                 GTK_MESSAGE_ERROR,
                                 GTK_BUTTONS_CLOSE,
                                 "Không thế thêm từ!\nLý do:Chưa nhập từ.");
gtk_window_set_title(GTK_WINDOW(dialog), "Lỗi!");
gtk_dialog_run (GTK_DIALOG (dialog));
gtk_widget_destroy (dialog);
}else
{
if(btsel(bt,(char*)wordget,mean,MEAN_LTH,&rsize)==0 )          
{
GtkWidget *dialog;
dialog = gtk_message_dialog_new (NULL,
                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                 GTK_MESSAGE_ERROR,
                                 GTK_BUTTONS_CLOSE,
                                 "Không thế thêm từ!\nLý do:Từ đã có sẵn trong từ điển.");
gtk_window_set_title(GTK_WINDOW(dialog), "Lỗi!");
gtk_dialog_run (GTK_DIALOG (dialog));
gtk_widget_destroy (dialog);
}else
{
    GtkWidget* dialog;
    GtkWidget* entry_dialog;
    const gchar* meanget;
    dialog = gtk_dialog_new_with_buttons("Nhập nghĩa cho từ!",
        GTK_WINDOW(app->window1),
        GTK_DIALOG_MODAL,
        GTK_STOCK_OK,GTK_RESPONSE_OK,
        GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
        NULL);
	gtk_container_set_border_width (GTK_CONTAINER (dialog), 20);
	entry_dialog = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),entry_dialog, 1,0, 0);
	gtk_widget_show_all(GTK_DIALOG(dialog)->vbox);
	gtk_window_set_title(GTK_WINDOW(dialog), "Nhập nghĩa!");
	    switch (gtk_dialog_run(GTK_DIALOG(dialog)))
    {
        
        case GTK_RESPONSE_OK:
            meanget = gtk_entry_get_text(GTK_ENTRY(entry_dialog));
	    add(bt,(char*)wordget,(char*)meanget);
	    gtk_label_set_text(GTK_LABEL(app->label1),"Từ đã được thêm");
	    gtk_list_store_clear(app->store);
for( i = 0; i < auto_complete((char*)wordget,out); i++ )
   {
      GtkTreeIter iter;
      gtk_list_store_append( app->store, &iter );
      gtk_list_store_set( app->store, &iter, 0,out[i].word, -1 );
   }
GtkWidget *view;
GtkTextBuffer *buf;
view = gtk_text_view_new ();
buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
gtk_text_buffer_set_text (buf,meanget, -1);
 gtk_text_view_set_buffer(GTK_TEXT_VIEW(app->textview1),buf);
            break;
       
        case GTK_RESPONSE_CANCEL:
        case GTK_RESPONSE_NONE:
        break;
    }
gtk_widget_destroy(dialog);
}
}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void on_xoa_clicked(GtkButton *button, AppWidgets *app)
{
const gchar *wordget= gtk_entry_get_text(GTK_ENTRY(app->entry2));
if(strcmp(wordget,"")==0){
GtkWidget *dialog;
dialog = gtk_message_dialog_new (NULL,
                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                 GTK_MESSAGE_ERROR,
                                 GTK_BUTTONS_CLOSE,
                                 "Không thế xóa từ!\nLý do:Chưa nhập từ");
gtk_window_set_title(GTK_WINDOW(dialog), "Lỗi!");
gtk_dialog_run (GTK_DIALOG (dialog));
gtk_widget_destroy (dialog);
}else
{
if(btsel(bt,(char*)wordget,mean,MEAN_LTH,&rsize)!=0 )                 //Neu ko thay
{
GtkWidget *dialog;
dialog = gtk_message_dialog_new ( NULL,
                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                 GTK_MESSAGE_ERROR,
                                 GTK_BUTTONS_CLOSE,
                                 "Không thế xóa từ!\nLý do:Không có từ cần xóa trong từ điển");
gtk_window_set_title(GTK_WINDOW(dialog), "Lỗi!");
gtk_dialog_run (GTK_DIALOG (dialog));
gtk_widget_destroy (dialog);
}
else
{
GtkWidget *dialog;
GtkResponseType response;
dialog = gtk_message_dialog_new (NULL,
                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                 GTK_MESSAGE_QUESTION,
                                 GTK_BUTTONS_YES_NO,
                                 "Bạn có chắc muốn xóa từ này?");
gtk_window_set_title(GTK_WINDOW(dialog), "Really delete?");
response = gtk_dialog_run (GTK_DIALOG (dialog));
gtk_widget_destroy (dialog);
if(response==GTK_RESPONSE_YES){delete(bt,(char*)wordget);gtk_label_set_text(GTK_LABEL(app->label1),"Từ đã bị xóa");
gtk_entry_set_text (GTK_ENTRY(app->entry2),"");gtk_list_store_clear(app->store);
for( i = 0; i < auto_complete("",out); i++ )
   {
      GtkTreeIter iter;
      gtk_list_store_append( app->store, &iter );
      gtk_list_store_set( app->store, &iter, 0,out[i].word, -1 );
   }
GtkWidget *view;
GtkTextBuffer *buf;
view = gtk_text_view_new ();
buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
gtk_text_buffer_set_text (buf,"", -1);
 gtk_text_view_set_buffer(GTK_TEXT_VIEW(app->textview1),buf);
}
}
}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void on_sua_clicked(GtkButton *button, AppWidgets *app)
{
const gchar *wordget= gtk_entry_get_text(GTK_ENTRY(app->entry2));
if(strcmp(wordget,"")==0){
GtkWidget *dialog;
dialog = gtk_message_dialog_new (NULL,
                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                 GTK_MESSAGE_ERROR,
                                 GTK_BUTTONS_CLOSE,
                                 "Không thế sửa từ!\nLý do:Chưa nhập từ");
gtk_window_set_title(GTK_WINDOW(dialog), "Lỗi!");
gtk_dialog_run (GTK_DIALOG (dialog));
gtk_widget_destroy (dialog);
}else
{
if(btsel(bt,(char*)wordget,mean,MEAN_LTH,&rsize)!=0 )                 //Neu ko thay
{
GtkWidget *dialog;
dialog = gtk_message_dialog_new (NULL,
                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                 GTK_MESSAGE_ERROR,
                                 GTK_BUTTONS_CLOSE,
                                 "Không thế sửa từ!\nLý do:Không có từ cần sửa trong từ điển");
gtk_window_set_title(GTK_WINDOW(dialog), "Lỗi!");
gtk_dialog_run (GTK_DIALOG (dialog));
gtk_widget_destroy (dialog);
}else
{
    GtkWidget* dialog;
    GtkWidget* entry_dialog;
    const gchar* meanget;
    dialog = gtk_dialog_new_with_buttons("Nhập nghĩa mới!",
        GTK_WINDOW(app->window1),
        GTK_DIALOG_MODAL,
        GTK_STOCK_OK,GTK_RESPONSE_OK,
        GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
        NULL);
	gtk_container_set_border_width (GTK_CONTAINER (dialog), 15);
	entry_dialog = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),entry_dialog, 1,0, 0);
	gtk_widget_show_all(GTK_DIALOG(dialog)->vbox);
	    switch (gtk_dialog_run(GTK_DIALOG(dialog)))
    {
        
        case GTK_RESPONSE_OK:
            meanget = gtk_entry_get_text(GTK_ENTRY(entry_dialog));
            delete(bt,(char*)wordget);
	    add(bt,(char*)wordget,(char*)meanget);
	    gtk_label_set_text(GTK_LABEL(app->label1),"Từ đã bị sửa");
GtkWidget *view;
GtkTextBuffer *buf;
view = gtk_text_view_new ();
buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
gtk_text_buffer_set_text (buf,meanget, -1);
 gtk_text_view_set_buffer(GTK_TEXT_VIEW(app->textview1),buf);
            break;
       
        case GTK_RESPONSE_CANCEL:
        case GTK_RESPONSE_NONE:
        break;
    }
gtk_widget_destroy(dialog);
}
}
}
/////////////////////////////////////////////////////////////////////////////
void on_button2_clicked(GtkWidget    *widget)
{
gtk_dialog_run(GTK_DIALOG(widget));
gtk_widget_hide(widget);
}
//////////////////////////////////////////////////////////////////////////////
void on_button3_clicked(GtkButton *button, AppWidgets *app)
{
GtkWidget *dialog;
dialog = gtk_file_chooser_dialog_new ("Open File",
				      NULL,
				      GTK_FILE_CHOOSER_ACTION_OPEN,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
				      NULL);
if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
  {
    char *filename;
    filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
     btcls(bt);
      bt=btopn(filename,0,1);
 gtk_list_store_clear(app->store);
for( i = 0; i < auto_complete("",out); i++ )
   {
      GtkTreeIter iter;
      gtk_list_store_append( app->store, &iter );
      gtk_list_store_set( app->store, &iter, 0,out[i].word, -1 );
   }
	gtk_label_set_text(GTK_LABEL(app->label1),"File đã được mở");
    g_free (filename);
  }
gtk_widget_destroy (dialog);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void on_them_activate(GtkWidget    *widget, AppWidgets *app)
{
const gchar *wordget= gtk_entry_get_text(GTK_ENTRY(app->entry2));
if(strcmp(wordget,"")==0){
GtkWidget *dialog;
dialog = gtk_message_dialog_new (NULL,
                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                 GTK_MESSAGE_ERROR,
                                 GTK_BUTTONS_CLOSE,
                                 "Không thế thêm từ!\nLý do:Chưa nhập từ");
gtk_window_set_title(GTK_WINDOW(dialog), "Lỗi!");
gtk_dialog_run (GTK_DIALOG (dialog));
gtk_widget_destroy (dialog);
}else
{
if(btsel(bt,(char*)wordget,mean,MEAN_LTH,&rsize)==0 )          
{
GtkWidget *dialog;
dialog = gtk_message_dialog_new (NULL,
                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                 GTK_MESSAGE_ERROR,
                                 GTK_BUTTONS_CLOSE,
                                 "Không thế thêm từ!\nLý do:Từ đã có sẵn trong từ điển");
gtk_window_set_title(GTK_WINDOW(dialog), "Lỗi!");
gtk_dialog_run (GTK_DIALOG (dialog));
gtk_widget_destroy (dialog);
}else
{
    GtkWidget* dialog;
    GtkWidget* entry_dialog;
    const gchar* meanget;
    dialog = gtk_dialog_new_with_buttons("Nhập nghĩa cho từ!",
        GTK_WINDOW(app->window1),
        GTK_DIALOG_MODAL,
        GTK_STOCK_OK,GTK_RESPONSE_OK,
        GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
        NULL);
	gtk_container_set_border_width (GTK_CONTAINER (dialog), 20);
	entry_dialog = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),entry_dialog, 1,0, 0);
	gtk_widget_show_all(GTK_DIALOG(dialog)->vbox);
	gtk_window_set_title(GTK_WINDOW(dialog), "Nhập nghĩa!");
	    switch (gtk_dialog_run(GTK_DIALOG(dialog)))
    {
        
        case GTK_RESPONSE_OK:
            meanget = gtk_entry_get_text(GTK_ENTRY(entry_dialog));
	    add(bt,(char*)wordget,(char*)meanget);
	    gtk_label_set_text(GTK_LABEL(app->label1),"Từ đã được thêm");
	    for( i = 0; i < auto_complete((char*)wordget,out); i++ )
   {
      GtkTreeIter iter;
      gtk_list_store_append( app->store, &iter );
      gtk_list_store_set( app->store, &iter, 0,out[i].word, -1 );
   }
GtkWidget *view;
GtkTextBuffer *buf;
view = gtk_text_view_new ();
buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
gtk_text_buffer_set_text (buf,meanget, -1);
 gtk_text_view_set_buffer(GTK_TEXT_VIEW(app->textview1),buf);
            break;
       
        case GTK_RESPONSE_CANCEL:
        case GTK_RESPONSE_NONE:
        break;
    }
gtk_widget_destroy(dialog);
}
}
}
///////////////////////////////////////////////////////////////////////////////
void on_xoa_activate(GtkWidget    *widget, AppWidgets *app)
{
const gchar *wordget= gtk_entry_get_text(GTK_ENTRY(app->entry2));
if(strcmp(wordget,"")==0){
GtkWidget *dialog;
dialog = gtk_message_dialog_new (NULL,
                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                 GTK_MESSAGE_ERROR,
                                 GTK_BUTTONS_CLOSE,
                                 "Không thế xóa từ!\nLý do:Chưa nhập từ");
gtk_window_set_title(GTK_WINDOW(dialog), "Lỗi!");
gtk_dialog_run (GTK_DIALOG (dialog));
gtk_widget_destroy (dialog);
}else
{
if(btsel(bt,(char*)wordget,mean,MEAN_LTH,&rsize)!=0 )                 //Neu ko thay
{
GtkWidget *dialog;
dialog = gtk_message_dialog_new ( NULL,
                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                 GTK_MESSAGE_ERROR,
                                 GTK_BUTTONS_CLOSE,
                                 "Không thế xóa từ!\nLý do:Không có từ cần xóa trong từ điển");
gtk_window_set_title(GTK_WINDOW(dialog), "Lỗi!");
gtk_dialog_run (GTK_DIALOG (dialog));
gtk_widget_destroy (dialog);
}
else
{
GtkWidget *dialog;
GtkResponseType response;
dialog = gtk_message_dialog_new (NULL,
                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                 GTK_MESSAGE_QUESTION,
                                 GTK_BUTTONS_YES_NO,
                                 "Bạn có chắc muốn xóa từ này?");
gtk_window_set_title(GTK_WINDOW(dialog), "Really delete?");
response = gtk_dialog_run (GTK_DIALOG (dialog));
gtk_widget_destroy (dialog);
if(response==GTK_RESPONSE_YES){delete(bt,(char*)wordget);gtk_label_set_text(GTK_LABEL(app->label1),"Từ đã bị xóa");
gtk_entry_set_text (GTK_ENTRY(app->entry2),"");gtk_list_store_clear(app->store);
for( i = 0; i < auto_complete("",out); i++ )
   {
      GtkTreeIter iter;
      gtk_list_store_append( app->store, &iter );
      gtk_list_store_set( app->store, &iter, 0,out[i].word, -1 );
   }
GtkWidget *view;
GtkTextBuffer *buf;
view = gtk_text_view_new ();
buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
gtk_text_buffer_set_text (buf,"", -1);
 gtk_text_view_set_buffer(GTK_TEXT_VIEW(app->textview1),buf);
}
}
}
}
///////////////////////////////////////////////////////////////////////////
void on_sua_activate(GtkWidget    *widget, AppWidgets *app)
{
const gchar *wordget= gtk_entry_get_text(GTK_ENTRY(app->entry2));
if(strcmp(wordget,"")==0){
GtkWidget *dialog;
dialog = gtk_message_dialog_new (NULL,
                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                 GTK_MESSAGE_ERROR,
                                 GTK_BUTTONS_CLOSE,
                                 "Không thế sửa từ!\nLý do:Chưa nhập từ");
gtk_window_set_title(GTK_WINDOW(dialog), "Lỗi!");
gtk_dialog_run (GTK_DIALOG (dialog));
gtk_widget_destroy (dialog);
}else
{
if(btsel(bt,(char*)wordget,mean,MEAN_LTH,&rsize)!=0 )                 //Neu ko thay
{
GtkWidget *dialog;
dialog = gtk_message_dialog_new (NULL,
                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                 GTK_MESSAGE_ERROR,
                                 GTK_BUTTONS_CLOSE,
                                 "Không thế sửa từ!\nLý do:Không có từ cần sửa trong từ điển");
gtk_window_set_title(GTK_WINDOW(dialog), "Lỗi!");
gtk_dialog_run (GTK_DIALOG (dialog));
gtk_widget_destroy (dialog);
}else
{
    GtkWidget* dialog;
    GtkWidget* entry_dialog;
    const gchar* meanget;
    dialog = gtk_dialog_new_with_buttons("Nhập nghĩa mới!",
        GTK_WINDOW(app->window1),
        GTK_DIALOG_MODAL,
        GTK_STOCK_OK,GTK_RESPONSE_OK,
        GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
        NULL);
	gtk_container_set_border_width (GTK_CONTAINER (dialog), 15);
	entry_dialog = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),entry_dialog, 1,0, 0);
	gtk_widget_show_all(GTK_DIALOG(dialog)->vbox);
	    switch (gtk_dialog_run(GTK_DIALOG(dialog)))
    {
        
        case GTK_RESPONSE_OK:
            meanget = gtk_entry_get_text(GTK_ENTRY(entry_dialog));
            delete(bt,(char*)wordget);
	    add(bt,(char*)wordget,(char*)meanget);
	    gtk_label_set_text(GTK_LABEL(app->label1),"Từ đã bị sửa");
GtkWidget *view;
GtkTextBuffer *buf;
view = gtk_text_view_new ();
buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
gtk_text_buffer_set_text (buf,meanget, -1);
 gtk_text_view_set_buffer(GTK_TEXT_VIEW(app->textview1),buf);
            break;
       
        case GTK_RESPONSE_CANCEL:
        case GTK_RESPONSE_NONE:
        break;
    }
gtk_widget_destroy(dialog);
}
}
}
////////////////////////////////////////////////////////////////////////
