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

glm::mat4 Multiply( glm::mat4 a, glm::mat4 b );
glm::vec3 Multiply( glm::mat4 a, glm::vec3 b );
glm::vec3 ScalePointAroundAnotherPoint( glm::vec3 inputPoint, glm::vec3 centerPoint, glm::vec3 scale );
glm::vec3 RotatePointAroundAnotherPoint( glm::vec3 inputPoint, glm::vec3 centerPoint, glm::mat4 first, glm::mat4 second, glm::mat4 third );
void PrintMatrix( glm::mat4 mat );

int main() {
  glm::vec3 one( 3., 9., 3. );
  glm::vec3 two( 2., 4., 3. );
  glm::vec3 nine( 8., 1., 2. );

  glm::vec4 three( 3., 6., 7., 4. );
  glm::vec4 four( 5., 6., 2., 6. );
  glm::vec4 five( 8., 1., 3., 5. );
  glm::vec4 six( 7., 9., 1., 7. );

  glm::mat4 seven( three, four, five, six );
  glm::mat4 eight( five, four, six, three );
  glm::mat4 ten( six, four, three, five );

  glm::mat4 first = Multiply( seven, eight );
	PrintMatrix ( first );
  glm::vec3 second = Multiply( seven, one );
	fprintf( stderr, "mat and vec multiply= (%6.2f,%6.2f,%6.2f)\n", second.x, second.y, second.z );

  glm::vec3 third = ScalePointAroundAnotherPoint( one, two, nine );
  fprintf( stderr, "scale= (%6.2f,%6.2f,%6.2f)\n", third.x, third.y, third.z );

  glm::vec3 fourth = RotatePointAroundAnotherPoint( one, two, seven, eight, ten );
	fprintf( stderr, "rotate= (%6.2f,%6.2f,%6.2f)\n", fourth.x, fourth.y, fourth.z );

  return 0;
}

glm::mat4
Multiply( glm::mat4 a, glm::mat4 b )
{
  //The following simply multiplies the two mat4's together with the build in glm function
  glm::mat4 matAB = a * b;

  //The following returns the product of the multiplication
  return matAB;
}


glm::vec3
Multiply( glm::mat4 a, glm::vec3 b )
{
  //The following promotes the vec3 to a vec4 so that it can be multiplied by a mat4 using glm
  glm::vec4 Promoted = glm::vec4( b, 1. );
  glm::vec4 matAB = a * Promoted;

  //The following demotes the vec4 to a vec3 so that it can by returned
  glm::vec3 Demoted( matAB );

  //The following returns the demoted product of the vec4/mat4 multiplication
  return Demoted;
}


glm::vec3
ScalePointAroundAnotherPoint( glm::vec3 inputPoint, glm::vec3 centerPoint, glm::vec3 scale )
{
  //The following subtracts the center by the input so that we scale around the origin
  glm::vec3 subCI = inputPoint - centerPoint;

  //The following makes a mat4 becuase one is needed for scaling
  glm::mat4 matFour;

  //The following scales the mat4 by the scale given and then multiplies the scaled
  //value by the subtracted value and then adds the center point back in to move the point back
  glm::mat4 Scaled = glm::scale( matFour, scale );
  glm::vec3 Scaling = Multiply( Scaled, subCI);
  glm::vec3 ScalePAP = Scaling + centerPoint;

  //The following returns the scaled point
  return ScalePAP;
}


glm::vec3
RotatePointAroundAnotherPoint( glm::vec3 inputPoint, glm::vec3 centerPoint, glm::mat4 first, glm::mat4 second, glm::mat4 third )
{
  //The following subtracts the centerPoint from the inputPoint
  glm::vec3 subCI = inputPoint - centerPoint;

  //The following multiplies the output of the subtraction by one, then two, then three
  //and then adds the center point back in to move the point back
  glm::vec3 turnOne = Multiply( first, subCI);
  glm::vec3 turnTwo = Multiply( second, turnOne);
  glm::vec3 Rotated = Multiply( third, turnTwo);
  glm::vec3 addRotate = Rotated + centerPoint;

  //The following returns the rotated point
  return Rotated;
}


void
WhoAmI( std::string &yourName, std::string &yourEmailAddress )
{
	yourName = "Nora Quick";
	yourEmailAddress = "nquick@oregonstate.edu" ;
}


void
PrintMatrix( glm::mat4 mat )
{
	for( int row = 0; row < 4; row++ )
	{
		fprintf( stderr, "  %7.2f %7.2f %7.2f %7.2f\n", mat[row][0], mat[row][1], mat[row][2], mat[row][3] );
	}
}
