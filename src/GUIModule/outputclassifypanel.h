#ifndef OUTPUTCLASSIFYPANEL_H
#define OUTPUTCLASSIFYPANEL_H

#include "IObserver.h"
#include "ManagerModule/Manager.h"
#include "Subject.h"

#include <QWidget>
#include <QGridLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

/**
 * Class OutputClassifyPanel. Representation of output data.
 */
class OutputClassifyPanel : public QWidget, public IObserver
{
    Q_OBJECT

public:
    /**
     * Constructor for class OutputClassifyPanel.
     * @param parent
     */
    OutputClassifyPanel(QWidget *parent = nullptr);

    /**
     * Destructor for class OutputClassifyPanel.
     */
    ~OutputClassifyPanel();

    /**
     * Add images preview to output panel.
     * @param previewImages vectot of all preview of images
     */
    void addPreviewImages(QVector<QPair<QLabel*, QPixmap> > previewImages);

    /**
     * Clear OutputClassifyPanel of output data.
     */
    void clearPanel();

    /**
    * @return whether this tab is classify tab
    */
    inline bool isClassifyTab() override {return classifyTab;}

    /**
     * @param manager manager to set
     */
    inline void setManager(Manager* manager) {this->manager = manager;}

    /**
     * @param results results of process to set
     */
    void setResults(vector<string>& results);

    /**
     * Invoke the update methods on output panel.
     */
    void invokeUpdate() override;

    /**
     * Print log of transfer learning.
     */
    void addTrainingLog();

    /**
     * Add training accuracy curve to output panel.
     */
    void addTrainingAccuracyCurve();

    /**
     * Print line of text to output panel.
     * @param line text
     */
    void addLine(string line);

    /**
     * Add training loss curve to output panel.
     */
    void addTrainingLossCurve();

    /**
     * @param classifyTab classifyTab to set
     */
    inline void setClassifyTab(bool classifyTab) {this->classifyTab = classifyTab;}

protected:
    /**
     * Adjust input image for scroll area.
     * @param event
     */
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    //const string PROJECT_DIR = "/home/viet/CLionProjects/AlexLens/resources/"; /// Current path of project directory
    vector<string> results; /// Vector of results of process
    QGridLayout* m_gridLayout; /// The main panel of OutputClassifyPanel
    QGridLayout* m_gridLayout_2; /// The panel with all output data
    QScrollArea* m_scrollArea; /// Scroll area
    QVBoxLayout* m_verticalLayout; /// Vertical Layout for input data
    QWidget*     m_scrollAreaWidgetContents; /// Scroll widget
    QVector<QPair<QLabel*, QPixmap> > previewImages; /// Vector of all preview of added images
    QVector<QLabel*> classifyResults; /// Vector of results of classify
    bool classifyTab = true; /// bool flag for tabs
    Manager* manager; /// The main manager of program
};

#endif // WIDGET_H
