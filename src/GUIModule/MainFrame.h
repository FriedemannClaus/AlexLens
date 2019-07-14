/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _MAINFRAME_H
#define _MAINFRAME_H

#include "GUIModule/IView.h"


class MainFrame: public IView {
private: 
	ClassifyFrame classifyFrame;
	TrainingFrame trainingFrame;
};

#endif //_MAINFRAME_H