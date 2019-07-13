/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _TRAININGFRAME_H
#define _TRAININGFRAME_H

#include "IView.h"


class TrainingFrame: public IView {
private: 
	InputPanel inputPanel;
	ParameterPanel paramPanel;
	OutputTrainingPanel outputTrainingPanel;
	StatisticHelpPanel statHelpPanel;
};

#endif //_TRAININGFRAME_H