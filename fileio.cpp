#ifndef _FILEIO_CPP_
#define _FILEIO_CPP_

#include <iostream>
#include <fstream>
#include <string>
#include "fileio.h"
#include "raytrace.h"
#define FILENAME "scene.obj"

using namespace std;

//string globalFaces[1000];
//int globalFaceCount = 0;
/*
void save( void )
{
	extern TreDEngine *globalEngine;
	ofstream file;
	file.open( FILENAME, ios::out );
	for( int i = 0; i < globalEngine->numPoly; i ++ )
	{
		if( globalEngine->polygons[ i ].num > 0 )
			file << "o" << endl;

		for( int j = 0; j < globalEngine->polygons[ i ].num; j++ )
		{
			file << "v " << globalEngine->polygons[ i ].x[j] << " " << globalEngine->polygons[ i ].y[j] << " " << globalEngine->polygons[ i ].z[j] << endl;
		}
	}

	for( int i = 0; i < globalFaceCount; i++ )
		file << globalFaces[i] << endl;

}*/


void read( rayEngine &engine )
{
	char c;
	float x, y, z;
	string line;
	ifstream file;
	int tmpVerts[ 1000 ];
	int tmpNum;
	vec3* verts = new vec3[ 1000 ];
	int numVerts = 0;
	int vertOffset = 0;

//	int iNxt; //used in accordance with i from a for loop and it loops around

	file.open( FILENAME , ios::in );

	if( !file.is_open() )
		return;

	engine.numPoly = 0;

	while( !file.eof() )
	{
		getline( file, line );
		if( line.length() < 2 )
			continue;

		if( line[0] == 'o' && numVerts != 0 )
		{
			engine.numPoly++;
			vertOffset = numVerts;
		}

		if( line[0] == 'v' && line[1] != 'n' )
		{
			sscanf( line.c_str() , "%c %f %f %f", &c, &x, &y, &z );
			
			verts[ numVerts ][0] = x;
			verts[ numVerts ][1] = y;
			verts[ numVerts ][2] = z;
			numVerts++;

			engine.polygons[ engine.numPoly ].insert( x, y, z );
		}

		if( line[0] == 'v' && line[1] == 'n' )
		{
			sscanf( line.c_str() , "%c%c %f %f %f", &c, &c, &x, &y, &z );
			engine.polygons[ engine.numPoly ].insertNorm( x, y, z );
		}

		if( line[0] == 'f' )
		{
//			globalFaces[globalFaceCount] = line;
//			globalFaceCount++;
			tmpNum = 0;
			for( unsigned int cur = 1; cur < line.length(); cur++ )
			{
				if( line[cur] == ' ' )
					continue;

				if( line[cur - 1] != ' ' )
					continue;

				tmpVerts[ tmpNum ] = atoi( line.c_str() + cur );
				tmpVerts[ tmpNum ] -= 1+vertOffset;
				tmpNum++;
				
			}

			engine.polygons[ engine.numPoly ].insertTriangle( tmpVerts, tmpNum );

			/*for( int i = 0; i < tmpNum; i++ )
			{
				iNxt = (i == (tmpNum - 1))?0:(i+1);

				engine.polygons[ engine.numPoly ].edges[ engine.polygons[ engine.numPoly ].edgeCount ] = tmpVerts[i] -1 - vertOffset;

				engine.polygons[ engine.numPoly ].edgeCount++;
				engine.polygons[ engine.numPoly ].edges[ engine.polygons[ engine.numPoly ].edgeCount ] = tmpVerts[iNxt] -1 - vertOffset;

				engine.polygons[ engine.numPoly ].edgeCount++;
			}*/
		}
	}


	engine.numPoly++;


	file.close();

}

#endif