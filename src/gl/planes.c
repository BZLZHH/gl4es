#include "planes.h"

#include "../glx/hardext.h"
#include "loader.h"
#include "matrix.h"
#include "matvec.h"

void APIENTRY_GL4ES gl4es_glClipPlanef(GLenum plane, const GLfloat *equation)
{
    /*
        When glClipPlane is called, 
        equation is transformed by the inverse of the modelview matrix and stored in the resulting eye coordinates. 
        Subsequent changes to the modelview matrix have no effect on the stored plane-equation components. 
        If the dot product of the eye coordinates of a vertex with the stored plane equation components is positive or zero, 
        the vertex is in with respect to that clipping plane. Otherwise, it is out.
    */
    PUSH_IF_COMPILING(glClipPlanef);    //TODO: fix that, equation is an array and should be copied before being put in the stack
    if((plane<GL_CLIP_PLANE0) || (plane>=GL_CLIP_PLANE0+hardext.maxplanes)) {
        errorShim(GL_INVALID_ENUM);
        return;
    }
    // GLES2 clip plane handling
    int p = plane-GL_CLIP_PLANE0;
    matrix_vector(getInvMVMat(), equation, glstate->planes[p]); //Tested, seems ok
    noerrorShim();
}

AliasExport(void,glClipPlanef,,(GLenum pname, const GLfloat* params));
