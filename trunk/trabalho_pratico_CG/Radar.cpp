#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <IL/il.h>
#include <string.h>

#include "mapa.h"

double directionKey(Key key)
{
    double difx = key.pos_x - agent.pos_x;
    double difz = key.pos_z - agent.pos_z;

    //Verifica se difx � zero para n�o fazeres uma divis�o por zero (que � f�cil de ver qual o �ngulo nesse caso.
    //Podes tamb�m resolver logo o caso se difz for 0 que tamb�m � directo
    double key_angle = atan(difz/difx) * RAD;
    double agent_orientation = (agent.horizontal_angle) * RAD;

    if (agent.pos_x < key.pos_x)
        return key_angle + agent_orientation - 90; 

    else /*if (agent.pos_x > key.pos_x)*/
        return key_angle + agent_orientation + 90;
}