#include "musiceditorform.h"
#include "ui_musiceditorform.h"

#ifndef __APPLE__
#include "cqtmfc_famitracker.h"
#endif

MusicEditorForm::MusicEditorForm(QString fileName,QByteArray musicData,IProjectTreeViewItem* link,QWidget* parent) :
   CDesignerEditorBase(link,parent),
   ui(new Ui::MusicEditorForm)
{
   ui->setupUi(this);
#ifndef __APPLE__

   m_fileName = fileName;

   openFile("");

   ui->stackedWidget->addWidget(m_pMainFrame);
   ui->stackedWidget->setCurrentWidget(m_pMainFrame);

   QObject::connect(m_pMainFrame,SIGNAL(addToolBarWidget(QToolBar*)),this,SIGNAL(addToolBarWidget(QToolBar*)));
   QObject::connect(m_pMainFrame,SIGNAL(removeToolBarWidget(QToolBar*)),this,SIGNAL(removeToolBarWidget(QToolBar*)));
   QObject::connect(m_pMainFrame,SIGNAL(editor_modificationChanged(bool)),this,SLOT(editor_modificationChanged(bool)));
#endif
}

MusicEditorForm::~MusicEditorForm()
{
   delete ui;
}

void MusicEditorForm::editor_modificationChanged(bool m)
{
   setModified(m);

   emit editor_modified(m);
}

void MusicEditorForm::onSave()
{
#ifndef __APPLE__
   CDesignerEditorBase::onSave();

   CFamiTrackerDoc* pDoc = (CFamiTrackerDoc*)m_pMainFrame->GetActiveDocument();

   pDoc->OnSaveDocument((TCHAR*)m_fileName.toAscii().constData());

   setModified(false);
#endif
}
