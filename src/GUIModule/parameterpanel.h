#ifndef PARAMETERPANEL_H
#define PARAMETERPANEL_H

#include "ManagerModule/Manager.h"
#include "inputpanel.h"
#include "outputclassifypanel.h"

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>

using namespace std;

/**
 * Class ParameterPanel. Representation of available modes and neural networks.
 */
class ParameterPanel : public QWidget, public IObserver
{
    Q_OBJECT

public:
    /**
    * @return whether this tab is classify tab
    */
    inline bool isClassifyTab() override {return classifyTab;}


    /**
     * Constructor for class ParameterPanel.
     * @param parent
     */
    ParameterPanel(QWidget *parent = 0);

    /**
     * Destructor for class ParameterPanel.
     */
    ~ParameterPanel();

    /**
     * Fill parameter box with available modes.
     */
    void fillModes();

    /**
     * Fill parameter box with available neural networks.
     */
    void fillNeuralNets();

    /**
     * @param classifyTab classifyTab to set
     */
    inline void setClassifyTab(bool classifyTab) {this->classifyTab = classifyTab;}

    /**
     * @param manager manager to set
     */
    inline void setManager(Manager* manager) {this->manager = manager;}

    /**
     * @param inputPanel inputPanel to set
     */
    inline void setInputPanel(InputPanel* inputPanel) {this->inputPanel = inputPanel;}

    /**
     * @param outputPanel outputPanel to set
     */
    inline void setOutputPanel(OutputClassifyPanel* outputPanel) {this->outputPanel = outputPanel;}

    /**
     * Invoke the update methods on parameter panel.
     */
    void invokeUpdate() override;

private slots:
    /**
     * Start process (classify or transfer learning).
     */
    void start();

    /**
     * Reset all input in panels (classify or transfer learning).
     */
    void reset();

private:
    QGridLayout* m_gridLayout; /// The main panel of OutputClassifyPanel
    QPushButton* m_pushButton; /// Stop button
    QPushButton* m_pushButton2; /// Start button
    QListWidget* modList; /// List of all available modes
    QListWidget* neuralNetsList; /// List of all available neural networks
    Manager* manager; /// The main manager of program
    InputPanel* inputPanel; /// Input panel
    OutputClassifyPanel* outputPanel; /// Output panel
    bool runWasPushed = false; /// bool flag for start button
    bool classifyTab = true; /// bool flag for tabs
};

#endif // WIDGET_H
