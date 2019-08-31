#ifndef INPUTPANEL_H
#define INPUTPANEL_H

#include <QWidget>
#include <QGridLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QMimeData>

#include "ManagerModule/Manager.h"

/**
 * Class InputPanel. Representation of input data.
 */
class InputPanel : public QWidget
{
    Q_OBJECT

public:
    /**
     * Constructor for class InputPanel.
     * @param parent
     */
    InputPanel(QWidget *parent = nullptr);

    /**
     * Destructor for class InputPanel.
     */
    ~InputPanel();

    /**
     * @param manager manager to set
     */
    inline void setManager(Manager* manager) {this->manager = manager;}


    /**
     * @param classifyTab classifyTab to set
     */
    inline void setClassifyTab(bool classifyTab) {this->classifyTab = classifyTab;}

    /**
     * @return whether image/directory was added
     */
    inline bool isImageAdded() {
        if (this->previewImages.size() > 0) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * @return all preview of added images
     */
    inline QVector<QPair<QLabel*, QPixmap> > getPreviewImages() {return this->previewImages;}

    /**
     * Delete all objects from vector of images preview.
     */
    inline void clearPreviewImages() {this->previewImages.clear();}

    /**
     * Clear InputPanel of input data.
     */
    void clearPanel();

    inline void setButtonText(string text){m_pushButton->setText(QString::fromStdString(text));}

private slots:
    /**
     * Add input data to InputPanel.
     */
    void addImage();

    /**
     * Check drag&drop input data.
     * @param e
     */
    void dragEnterEvent(QDragEnterEvent *e) override;

    /**
     * Add drag&drop input data to InputPanel.
     * @param e
     */
    void dropEvent(QDropEvent *e) override;

protected:
    /**
     * Adjust input image for scroll area.
     * @param event
     */
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    QGridLayout* m_gridLayout; /// The main panel of InputPanel
    QGridLayout* m_gridLayout_2; /// The panel with all input data
    QScrollArea* m_scrollArea; /// Scroll area
    QPushButton* m_pushButton; /// Button to open file dialog for choosing input data
    QVBoxLayout* m_verticalLayout; /// Vertical Layout for input data
    QWidget*     m_scrollAreaWidgetContents; /// Scroll widget
    QVector<QPair<QLabel*, QPixmap> > previewImages; /// Vector of all preview of added images
    Manager* manager; /// The main manager of program
    bool classifyTab = true; /// bool flag for tabs
};

#endif // WIDGET_H
