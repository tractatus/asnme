#include "mongoexplorermodel.h"
#include "preferences.h"
#include "mongoserver.h"

MongoExplorerModel::MongoExplorerModel(QObject *parent) :
    QStandardItemModel(parent)
{
    this->setColumnCount(1);
    QStringList labels;
    labels.append(tr("Explorer"));
    this->setHorizontalHeaderLabels(labels);
    updateTree();
}

void MongoExplorerModel::updateTree()        
{
    // Get the list of servers from the preferences
    Preferences* prefs = Preferences::instance();
    QList<QStringList> servers = prefs->servers();

    MongoServer *prefServer;

    // For each of the servers in the preferences
    foreach(QStringList settings, servers)
    {
        bool exists = false; // Does the
        MongoServer *treeServer;

        // Loop through the servers already in the tree
        // and, if it already exists, update the boolean to show this
        for(int i = 0; i < this->rowCount(); i++)
        {
          treeServer = (MongoServer*)this->item(i);
          QString newName = settings.first();
          if(treeServer->data(Qt::DisplayRole).toString() == newName)
          {
            exists = true;
          }
        }

        // If the server from the preferences doesn't already exist
        // in the tree then add it.
        if(exists == false)
        {
            prefServer = new MongoServer(settings);
            this->appendRow(prefServer);
        }
    }
}
