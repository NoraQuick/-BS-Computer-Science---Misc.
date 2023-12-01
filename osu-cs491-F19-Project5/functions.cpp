void
Animate( void )
{
	int i;				// counter
	struct fire *p;
	float dt;

	Time += Dt;
	if( Time > TMAX )
	{
		Time = 0.;
	}

	// ****************************************
	// Here is where you advance your particles to reflect the current Time:
	// ****************************************

	for( i=0, p=Fire; i < NUMFIRES; i++, p++ )
	{
		dt = Time - p->t0;
		p->x = p->x + (p->vx * dt);  //p->x + (p->vx * dt) + (.5 * GRAVITY * (dt * dt));   //p->x + (p->vx * dt);
		p->y = p->y + (p->vy * dt);  //p->y + (p->vy * dt) + (.5 * GRAVITY * (dt * dt));   //p->y + (p->vy * dt);   //p->y + (p->vy * dt) + (.5 * GRAVITY * (dt * dt));    //p[i].y + (p[i].vy * dt);
		p->z = p->z + (p->vz * dt) + (.5 * GRAVITY * (dt * dt));   //p->z + (p->vz * dt);
		p->r = 1.;
		p->g = 1.;
		p->b = 1.;
	}

	glutSetWindow( MainWindow );
	glutPostRedisplay();
}


void
InitGraphics( void )
{
	if( Debug )
		fprintf( stderr, "InitGraphics\n" );


	// setup the display mode:
	// ( *must* be done before call to glutCreateWindow() )
	// ask for color, double-buffering, and z-buffering:

	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );


	// set the initial window configuration:

	glutInitWindowPosition( 0, 0 );
	glutInitWindowSize( INIT_WINDOW_SIZE, INIT_WINDOW_SIZE );


	// open the window and set its title:

	MainWindow = glutCreateWindow( WINDOWTITLE );
	glutSetWindowTitle( WINDOWTITLE );


	// setup the clear values:

	glClearColor( BACKCOLOR[0], BACKCOLOR[1], BACKCOLOR[2], BACKCOLOR[3] );


	// setup the callback routines:


	// DisplayFunc -- redraw the window
	// ReshapeFunc -- handle the user resizing the window
	// KeyboardFunc -- handle a keyboard input
	// MouseFunc -- handle the mouse button going down or up
	// MotionFunc -- handle the mouse moving with a button down
	// PassiveMotionFunc -- handle the mouse moving with a button up
	// VisibilityFunc -- handle a change in window visibility
	// EntryFunc	-- handle the cursor entering or leaving the window
	// SpecialFunc -- handle special keys on the keyboard
	// SpaceballMotionFunc -- handle spaceball translation
	// SpaceballRotateFunc -- handle spaceball rotation
	// SpaceballButtonFunc -- handle spaceball button hits
	// ButtonBoxFunc -- handle button box hits
	// DialsFunc -- handle dial rotations
	// TabletMotionFunc -- handle digitizing tablet motion
	// TabletButtonFunc -- handle digitizing tablet button hits
	// MenuStateFunc -- declare when a pop-up menu is in use
	// TimerFunc -- trigger something to happen a certain time from now
	// IdleFunc -- what to do when nothing else is going on

	glutSetWindow( MainWindow );
	glutDisplayFunc( Display );
	glutReshapeFunc( Resize );
	glutKeyboardFunc( Keyboard );
	glutMouseFunc( MouseButton );
	glutMotionFunc( MouseMotion );
	glutPassiveMotionFunc( NULL );
	glutVisibilityFunc( Visibility );
	glutEntryFunc( NULL );
	glutSpecialFunc( NULL );
	glutSpaceballMotionFunc( NULL );
	glutSpaceballRotateFunc( NULL );
	glutSpaceballButtonFunc( NULL );
	glutButtonBoxFunc( NULL );
	glutDialsFunc( NULL );
	glutTabletMotionFunc( NULL );
	glutTabletButtonFunc( NULL );
	glutMenuStateFunc( NULL );
	glutTimerFunc( 0, NULL, 0 );

	// DO NOT SET THE GLUT IDLE FUNCTION HERE !!
	// glutIdleFunc( NULL );
	// let glui take care of it in InitGlui()


	// ****************************************
	// Here is where you setup your particle system data structures just once:
	// ****************************************

	Fire = new struct fire [ NUMFIRES ];
	int i;
	struct fire *p;
	for( i=0, p=Fire; i < NUMFIRES; i++, p++ )
	{
		p->x0 = XMIN + rand() % (int)(XMIN - XMAX);
		p->y0 = YMIN + rand() % (int)(YMIN - YMAX);
		p->z0 = ZMIN + rand() % (int)(ZMIN - ZMAX);
		float v = 0.;
		float th = 0.;
		p->vx = rand() % (int)(VELMAX - VELMIN);
		p->vy = rand() % (int)(VELMAX - VELMIN);
		p->vz = rand() % (int)(VELMAX - VELMIN);
		p->t0 = 0.;
		p->t1 = rand() % (int)TMAX;
		p->rad = 0.;
		p->r = 0.;
		p->g = 1.;
		p->b = 1.;
		p->ti = 0.;
		for( int j = 0; j < NUMTRACES; j++ )
		{
			p->tx[j] = 0.;
			p->ty[j] = 0.;
			p->tz[j] = 0.;
		}
	}
}

void
WhoAmI( std::string &yourName, std::string &yourEmailAddress )
{
        yourName = "Nora Quick";
        yourEmailAddress = "quickn@oregonstate.edu" ;
}
