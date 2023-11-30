#include <stdio.h>
#include <string>
#define _USE_MATH_DEFINES
#include <cmath>

#define GLM_FORCE_RADIANS
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"

glm::vec3 WhatPartOfALivesInBDir( glm::vec3 a, glm::vec3 b );
glm::vec3 WhatPartOfALivesPerpToB( glm::vec3 a, glm::vec3 b );
glm::vec3 UnitSurfaceNormal( glm::vec3 q, glm::vec3 r, glm::vec3 s );
float Area( glm::vec3 q, glm::vec3 r, glm::vec3 s );
bool IsPointInTriangle( glm::vec3 q, glm::vec3 r, glm::vec3 s, glm::vec3 p );
float DistanceFromPointToPlane( glm::vec3 q, glm::vec3 r, glm::vec3 s, glm::vec3 p );

int main(){
  glm::vec3 one( 3., 9., 3. );
  glm::vec3 two( 0., 0., 4. );
  glm::vec3 three( 12., 0., 5. );
  glm:: vec3 four( 5., 3., 3. );

  glm::vec3 l = WhatPartOfALivesInBDir(one, two);
	fprintf( stderr, "a in b dir= (%6.2f,%6.2f,%6.2f)\n", l.x, l.y, l.z );

  glm::vec3 m = WhatPartOfALivesPerpToB(one, two);
	fprintf( stderr, "a perp to b= (%6.2f,%6.2f,%6.2f)\n", m.x, m.y, m.z );

  glm::vec3 n = UnitSurfaceNormal(one, two, three);
	fprintf( stderr, "normal= (%6.2f,%6.2f,%6.2f)\n", n.x, n.y, n.z );

  float o = Area( one, two, three );
	fprintf( stderr, "area= (%6.2f)\n", o );

  bool t = IsPointInTriangle( one, two, three, four );
	if(t){
		printf("true\n");
	}
	else{
		printf("false\n");
	}

  float u = DistanceFromPointToPlane( one, two, three, four );
	fprintf( stderr, "distance= (%6.2f)\n", u );

  return 0;
}

glm::vec3
WhatPartOfALivesInBDir( glm::vec3 a, glm::vec3 b )
{
	//B-hat(A * B-hat)
	//The following does the section inside the parentheses
	glm::vec3 bhat = glm::normalize( b );
	float c = glm::dot( a, bhat );

	//The following does the outside * the inside and returns the outcome
	return c * bhat;
}


glm::vec3
WhatPartOfALivesPerpToB( glm::vec3 a, glm::vec3 b )
{
	//A-B-hat(A * B-hat)
	//The folowing does second half of the equation
	glm::vec3 bhat = glm::normalize( b );
	float c = glm::dot( a, bhat );
	glm::vec3 d = c * bhat;

	//The following subtracts A by the second half and returns the outcome
	return a - d;
}


glm::vec3
UnitSurfaceNormal( glm::vec3 q, glm::vec3 r, glm::vec3 s )
{
	//n = (R - Q) * (S - Q)
	//The following finds the cross product of the two subtracted variables
	glm::vec3 normal = glm::cross( r-q, s-q );

	//The following noramlized the cross product and returns the outcome
	return glm::normalize( normal );
}


float
Area( glm::vec3 q, glm::vec3 r, glm::vec3 s )
{
	//.5 * ||(R - Q) * (S - Q)||
	//The following finds the cross product and the magnitude (length) and
	//multiplies the outcome by half and the returns the total outcome
	return .5 * glm::length( glm::cross( r-q, s-q ) );
}


bool
IsPointInTriangle( glm::vec3 q, glm::vec3 r, glm::vec3 s, glm::vec3 p )
{
	//n = (point - point) * (point - point) & (n * n(q,r,s))
	//The following finds the output of each subtraction needed for the four
	//equations that will be crossed together.
	glm::vec3 r_q = r - q;
	glm::vec3 s_q = s - q;
	glm::vec3 p_q = p - q;
	glm::vec3 s_r = s - r;
	glm::vec3 p_r = p - r;
	glm::vec3 q_s = q - s;
	glm::vec3 p_s = p - s;

	//The following finds the cross product of the two varibale need for
	//each of the four equations
	glm::vec3 nn = glm::cross( r_q, s_q );
	glm::vec3 nq = glm::cross( r_q, p_q );
	glm::vec3 nr = glm::cross( s_r, p_r );
	glm::vec3 ns = glm::cross( q_s, p_s );

	//The following finds the dot products needed to check if the outputs
	//are positive or not
	float first = glm::dot( nn, nq );
	float second = glm::dot( nn, nr );
	float third = glm::dot (nn, ns );

	//The following checks if the outputs of the three dot products are
	//positive or not and returns a boolian
	if( first >= 0 && second >= 0 && third >= 0 ) {
		return true;
	}
	else {
		return false;
	}
}



float
DistanceFromPointToPlane( glm::vec3 q, glm::vec3 r, glm::vec3 s, glm::vec3 p )
{
	//d = (P - Q) * N-hat
	//The following finds the surface normal using the previous normal
	//function
	glm::vec3 normal = UnitSurfaceNormal( q, r, s );

	//The following finds p - q and then finds the dot product of the
	//outcome with the normal
	glm::vec3 pq = p - q;
	float distance = glm::dot( pq, normal );

	//The following outputs the outcome of the dot product
	return distance;
}


void
WhoAmI( std::string &yourName, std::string &yourEmailAddress )
{
	yourName = "Nora Quick";
	yourEmailAddress = "quickn@oregonstate.edu" ;
}
