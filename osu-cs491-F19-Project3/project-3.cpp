Forward(float th1, float th2, float th3, float l1, float l2,
	glm::mat4 & x1g, glm::mat4 & x2g, glm::mat4 & x3g)
{
  //The following is code given by professor Bailey
	glm::mat4 tl1 = glm::mat4();
	glm::mat4 tl2 = glm::mat4();
	glm::mat4 r1 = glm::mat4();
	glm::mat4 r2 = glm::mat4();
	glm::mat4 r3 = glm::mat4();
	glm::mat4 x21 = glm::mat4();
	glm::mat4 x32 = glm::mat4();

	th1 *= (M_PI / 180.);
	th2 *= (M_PI / 180.);
	th3 *= (M_PI / 180.);

	x1g = glm::mat4( );
	x2g = glm::mat4( );
	x3g = glm::mat4( );

  //The following makes three vec3s for the lengths of two of the things we need to move and a third
  ///vec3 for the first thing that we simply rotate but do not move. We make it with the length so that
  //we can translate the second two things to their correct position.
	glm::vec3 vectorRot = glm::vec3(0., 0., 1.);
	glm::vec3 vectorTwo = glm::vec3(l2, 0., 0.);
	glm::vec3 vectorOne = glm::vec3(l1, 0., 0.);

  //We have to rotate and then translate the last thing so we simply do that
	glm::mat4 rotateThree = glm::rotate(x3g, th3, vectorRot);
	glm::mat4 translateThree = glm::translate(x3g, vectorTwo);

  //We have to rotate and then tanslate the second thing so we simply do that
	glm::mat4 rotateTwo = glm::rotate(x2g, th2, vectorRot);
	glm::mat4 translateTwo = glm::translate(x2g, vectorOne);

  //We only have to rotate the first thing so we simply rotate it
	glm::mat4 rotateOne = glm::rotate(x1g, th1, vectorRot);

  //We need to first rotate the first thing to be at the correct angle. Then we need to multiply the firsts position
  //with the second's translation and rotation to make sure the second thing is at the end of the first one
  //and that it is at the right angle. We then need to multiply the seconds position by the third one so that
  //we have it at the end of the second thing and at the correct angle.
	x1g = rotateOne;
	x2g = x1g * translateTwo * rotateTwo;
	x3g = x2g * translateThree * rotateThree;
}

void
WhoAmI( std::string &yourName, std::string &yourEmailAddress )
{
  yourName = "Nora Quick";
  yourEmailAddress = "quickn@oregonstate.edu" ;
}
