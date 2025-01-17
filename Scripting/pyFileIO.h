PyMethodDef irr_FileIO[] = {
{"tiled",Python::PyIrr_Tiled,METH_VARARGS,"tiled"},
//{"zistream",Python::PyIrr_zistream,METH_VARARGS,"sets camera vector"},
    {"zistream",Python::PyIrr_zistream,METH_VARARGS,"sets camera vector"},
    {"zostream",Python::PyIrr_zostream,METH_VARARGS,"sets camera vector"},
	{"files",Python::PyIrr_FileArchive,METH_VARARGS,"file archive manager"},
	{NULL,NULL,0,NULL}
};


ITimer* timer ;
	s32 currentFrameIndex = 0;
	f32 currentFrameTime = 0;
	f32 deltaTime, oldTime = 0;

PyObject * Python::PyIrr_Tiled(PyObject * self,PyObject * args){
	char * t;
	int test=0;
	PyArg_ParseTuple(args,"si",&t, &test);

		timer = device->getTimer();
#ifdef TILED2D
switch (test){

    case 0:{
        tld = new irrTiled(t,device);
        //tld = new irrTiled("../media/tiled2d/2dbasic.tmx",device);
    }break;

    case 1:{
        // Extracts data from all tile sets.
		for (u32 i = 0; i < tld->tileset.size(); ++i)
		{
			TILESET ts = tld->tileset[i];

			// Extracts data from all layers.
			for (u32 j = 0; j < tld->layer.size(); ++j)
			{
				LAYER lyr = tld->layer[j];

				for (u32 d = 0; d < lyr.data.size(); ++d)
				{
					s32 id = lyr.data[d] - ts.firstgid;
					if (id >= 0)
					{
						// Tile position.
						s32 x = (d % lyr.width) * tld->tileWidth;
						s32 y = (d / lyr.width) * tld->tileHeight;

						// Draw the tile.
						driver->draw2DImage(ts.img.tex, vector2di(x, y), ts.subRects[id], 0, lyr.tintColor, true);
					}
				}
			}
		}
 }break;
 case 2:{
 		// For the animations I use a "delta time".
		deltaTime = timer->getTime() - oldTime;

		// Extracts data from all tile sets.
		for (u32 i = 0; i < tld->tileset.size(); ++i)
		{
			TILESET ts = tld->tileset[i];

			// Extracts data from all layers.
			for (u32 j = 0; j < tld->layer.size(); ++j)
			{
				LAYER lyr = tld->layer[j];

				// The array "lyr.data" contains all the ids of the tiles, in this way it can be used to identify
				// in an image the position of the section to be drawn.
				for (u32 d = 0; d < lyr.data.size(); ++d)
				{
					s32 id = lyr.data[d] - ts.firstgid;
					if (id >= 0)
					{
						// Tile position.
						s32 x = (d % lyr.width) * tld->tileWidth;
						s32 y = (d / lyr.width) * tld->tileHeight;

						// Draw the tile.
						driver->draw2DImage(ts.img.tex, vector2di(x, y), ts.subRects[id], 0, lyr.tintColor, true);

						// This zone corresponds to the tiles extracted when using an external tileset.
						// In this case, the animation data they contain will be used.
						for (u32 j = 0; j < ts.tile.size(); ++j)
						{
							TILE tl = ts.tile[j];

							// In this way it is possible to make some tiles animated.
							// Sure there are other ways, this is just an example.
							if (tl.id == id && !tl.animation.empty())
							{
								currentFrameTime += 1.0f / deltaTime;

								s32 tileID = tl.animation[currentFrameIndex].tileid;
								s32 duration = tl.animation[currentFrameIndex].duration;

								if (currentFrameTime >= duration)
								{
									currentFrameTime = 0.f;

									if (currentFrameIndex == (tl.animation.size() - 1))
										currentFrameIndex = 0;
									else
										++currentFrameIndex;
								}

								// Draw the animation.
								driver->draw2DImage(ts.img.tex, vector2di(x, y), ts.subRects[tileID], 0, lyr.tintColor, true);
							}
						}

					}
				}
			}
		}

		oldTime = timer->getTime();
}break;
}

   // return Py_BuildValue("%l",tld);
   return Py_BuildValue("");
#else
    return Py_BuildValue("");
    #endif
}


PyObject * Python::PyIrr_FileArchive(PyObject * self,PyObject * args){
	char * t;
	PyArg_ParseTuple(args,"s",&t);
	device->getFileSystem()->addFileArchive( t );
	printf ("archive %s added to archive \n",t);
return Py_BuildValue("");
}

PyObject * Python::PyIrr_zistream(PyObject * self,PyObject * args){
	float x,y,z;
	int t;
	PyArg_ParseTuple(args,"s",&t,&x,&y,&z);
	#ifdef COMPRESS
	//def(stdin, stdout, Z_DEFAULT_COMPRESSION); //for compression
		inf(stdin, stdout);	//zpipe decompression
    #endif
    return Py_BuildValue("");
}


PyObject * Python::PyIrr_zostream(PyObject * self,PyObject * args){
	float x,y,z;
	int t;
	PyArg_ParseTuple(args,"ifff",&t,&x,&y,&z);
return Py_BuildValue("");
}
