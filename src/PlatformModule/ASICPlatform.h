/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _ASICPLATFORM_H
#define _ASICPLATFORM_H

#include "Platform.h"
#include "OpenVINO.h"


class ASICPlatform: public Platform, protected OpenVINO {
};

#endif //_ASICPLATFORM_H