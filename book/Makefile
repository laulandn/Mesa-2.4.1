
#CC=m68k-apple-macos-gcc
#CXX=m68k-apple-macos-g++
#CC=powerpc-apple-macos-gcc
#CXX=powerpc-apple-macos-g++

CFLAGS= -I../include -I/opt/local/include
LDFLAGS=-lglu -lgl -lglut -lm -L/opt/local/include


OBJS=$(subst .c,.o,$(wildcard *.c))


.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<


all: $(OBJS) accanti accnot accpersp accum aim alpha alpha3D anti antiindex antipindex antipoint antipoly bezcurve bezmesh bezsurf checker checker2 chess clip colormat cone cube curve depthcue disk dof dofnot double drawf feedback fog fogindex font light linelist lines list list2 maplight material mipmap model movelight nurbs pickdepth pickline picksquare plane planet planetup polys robot sccolorlight scene scenebamb sceneflat select simple smooth sphere stencil stroke surface tea teaambient teapots texgen texturesurf trim xfont


accanti:	accanti.o
	$(CC) -o accanti accanti.o $(LDFLAGS)
#	../bin2app.sh accanti

accnot:	accnot.o
	$(CC) -o accnot accnot.o $(LDFLAGS)
#	../bin2app.sh accnot

accpersp:	accpersp.o
	$(CC) -o accpersp accpersp.o $(LDFLAGS)
#	../bin2app.sh accpersp

accum:	accum.o
	$(CC) -o accum accum.o $(LDFLAGS)
#	../bin2app.sh accum

aim:	aim.o
	$(CC) -o aim aim.o $(LDFLAGS)
#	../bin2app.sh aim

alpha:	alpha.o
	$(CC) -o alpha alpha.o $(LDFLAGS)
#	../bin2app.sh alpha

alpha3D:	alpha3D.o
	$(CC) -o alpha3D alpha3D.o $(LDFLAGS)
#	../bin2app.sh alpha3D

anti:	anti.o
	$(CC) -o anti anti.o $(LDFLAGS)
#	../bin2app.sh anti

antiindex:	antiindex.o
	$(CC) -o antiindex antiindex.o $(LDFLAGS)
#	../bin2app.sh antiindex

antipindex:	antipindex.o
	$(CC) -o antipindex antipindex.o $(LDFLAGS)
#	../bin2app.sh antipindex

antipoint:	antipoint.o
	$(CC) -o antipoint antipoint.o $(LDFLAGS)
#	../bin2app.sh antipoint

antipoly:	antipoly.o
	$(CC) -o antipoly antipoly.o $(LDFLAGS)
#	../bin2app.sh antipoly

bezcurve:	bezcurve.o
	$(CC) -o bezcurve bezcurve.o $(LDFLAGS)
#	../bin2app.sh bezcurve

bezmesh:	bezmesh.o
	$(CC) -o bezmesh bezmesh.o $(LDFLAGS)
#	../bin2app.sh bezmesh

bezsurf:	bezsurf.o
	$(CC) -o bezsurf bezsurf.o $(LDFLAGS)
#	../bin2app.sh bezsurf

checker:	checker.o
	$(CC) -o checker checker.o $(LDFLAGS)
#	../bin2app.sh checker

checker2:	checker2.o
	$(CC) -o checker2 checker2.o $(LDFLAGS)
#	../bin2app.sh checker2

chess:	chess.o
	$(CC) -o chess chess.o $(LDFLAGS)
#	../bin2app.sh chess

clip:	clip.o
	$(CC) -o clip clip.o $(LDFLAGS)
#	../bin2app.sh clip

colormat:	colormat.o
	$(CC) -o colormat colormat.o $(LDFLAGS)
#	../bin2app.sh colormat

cone:	cone.o
	$(CC) -o cone cone.o $(LDFLAGS)
#	../bin2app.sh cone

cube:	cube.o
	$(CC) -o cube cube.o $(LDFLAGS)
#	../bin2app.sh cube

curve:	curve.o
	$(CC) -o curve curve.o $(LDFLAGS)
#	../bin2app.sh curve

depthcue:	depthcue.o
	$(CC) -o depthcue depthcue.o $(LDFLAGS)
#	../bin2app.sh depthcue

disk:	disk.o
	$(CC) -o disk disk.o $(LDFLAGS)
#	../bin2app.sh disk

dof:	dof.o
	$(CC) -o dof dof.o $(LDFLAGS)
#	../bin2app.sh dof

dofnot:	dofnot.o
	$(CC) -o dofnot dofnot.o $(LDFLAGS)
#	../bin2app.sh dofnot

double:	double.o
	$(CC) -o double double.o $(LDFLAGS)
#	../bin2app.sh double

drawf:	drawf.o
	$(CC) -o drawf drawf.o $(LDFLAGS)
#	../bin2app.sh drawf

feedback:	feedback.o
	$(CC) -o feedback feedback.o $(LDFLAGS)
#	../bin2app.sh feedback

fog:	fog.o
	$(CC) -o fog fog.o $(LDFLAGS)
#	../bin2app.sh fog

fogindex:	fogindex.o
	$(CC) -o fogindex fogindex.o $(LDFLAGS)
#	../bin2app.sh fogindex

font:	font.o
	$(CC) -o font font.o $(LDFLAGS)
#	../bin2app.sh font

light:	light.o
	$(CC) -o light light.o $(LDFLAGS)
#	../bin2app.sh light

linelist:	linelist.o
	$(CC) -o linelist linelist.o $(LDFLAGS)
#	../bin2app.sh linelist

lines:	lines.o
	$(CC) -o lines lines.o $(LDFLAGS)
#	../bin2app.sh lines

list:	list.o
	$(CC) -o list list.o $(LDFLAGS)
#	../bin2app.sh list

list2:	list2.o
	$(CC) -o list2 list2.o $(LDFLAGS)
#	../bin2app.sh list2

maplight:	maplight.o
	$(CC) -o maplight maplight.o $(LDFLAGS)
#	../bin2app.sh maplight

material:	material.o
	$(CC) -o material material.o $(LDFLAGS)
#	../bin2app.sh material

mipmap:	mipmap.o
	$(CC) -o mipmap mipmap.o $(LDFLAGS)
#	../bin2app.sh mipmap

model:	model.o
	$(CC) -o model model.o $(LDFLAGS)
#	../bin2app.sh model

movelight:	movelight.o
	$(CC) -o movelight movelight.o $(LDFLAGS)
#	../bin2app.sh movelight

nurbs:	nurbs.o
	$(CC) -o nurbs nurbs.o $(LDFLAGS)
#	../bin2app.sh nurbs

pickdepth:	pickdepth.o
	$(CC) -o pickdepth pickdepth.o $(LDFLAGS)
#	../bin2app.sh pickdepth

pickline:	pickline.o
	$(CC) -o pickline pickline.o $(LDFLAGS)
#	../bin2app.sh pickline

picksquare:	picksquare.o
	$(CC) -o picksquare picksquare.o $(LDFLAGS)
#	../bin2app.sh picksquare

plane:	plane.o
	$(CC) -o plane plane.o $(LDFLAGS)
#	../bin2app.sh plane

planet:	planet.o
	$(CC) -o planet planet.o $(LDFLAGS)
#	../bin2app.sh planet

planetup:	planetup.o
	$(CC) -o planetup planetup.o $(LDFLAGS)
#	../bin2app.sh planetup

polys:	polys.o
	$(CC) -o polys polys.o $(LDFLAGS)
#	../bin2app.sh polys

robot:	robot.o
	$(CC) -o robot robot.o $(LDFLAGS)
#	../bin2app.sh robot

sccolorlight:	sccolorlight.o
	$(CC) -o sccolorlight sccolorlight.o $(LDFLAGS)
#	../bin2app.sh sccolorlight

scene:	scene.o
	$(CC) -o scene scene.o $(LDFLAGS)
#	../bin2app.sh scene

scenebamb:	scenebamb.o
	$(CC) -o scenebamb scenebamb.o $(LDFLAGS)
#	../bin2app.sh scenebamb

sceneflat:	sceneflat.o
	$(CC) -o sceneflat sceneflat.o $(LDFLAGS)
#	../bin2app.sh sceneflat

select:	select.o
	$(CC) -o select select.o $(LDFLAGS)
#	../bin2app.sh select

simple:	simple.o
	$(CC) -o simple simple.o $(LDFLAGS)
#	../bin2app.sh simple

smooth:	smooth.o
	$(CC) -o smooth smooth.o $(LDFLAGS)
#	../bin2app.sh smooth

sphere:	sphere.o
	$(CC) -o sphere sphere.o $(LDFLAGS)
#	../bin2app.sh sphere

stencil:	stencil.o
	$(CC) -o stencil stencil.o $(LDFLAGS)
#	../bin2app.sh stencil

stroke:	stroke.o
	$(CC) -o stroke stroke.o $(LDFLAGS)
#	../bin2app.sh stroke

surface:	surface.o
	$(CC) -o surface surface.o $(LDFLAGS)
#	../bin2app.sh surface

tea:	tea.o
	$(CC) -o tea tea.o $(LDFLAGS)
#	../bin2app.sh tea

teaambient:	teaambient.o
	$(CC) -o teaambient teaambient.o $(LDFLAGS)
#	../bin2app.sh teaambient

teapots:	teapots.o
	$(CC) -o teapots teapots.o $(LDFLAGS)
#	../bin2app.sh teapots

texgen:	texgen.o
	$(CC) -o texgen texgen.o $(LDFLAGS)
#	../bin2app.sh texgen

texturesurf:	texturesurf.o
	$(CC) -o texturesurf texturesurf.o $(LDFLAGS)
#	../bin2app.sh texturesurf

trim:	trim.o
	$(CC) -o trim trim.o $(LDFLAGS)
#	../bin2app.sh trim

xfont:	xfont.o
	$(CC) -o xfont xfont.o $(LDFLAGS)
#	../bin2app.sh xfont


clean:
	rm -f *.o *.bin *.pef *.APPL *.dsk *.gdb
	rm -f accanti accnot accpersp accum aim alpha alpha3D anti antiindex antipindex antipoint antipoly bezcurve bezmesh bezsurf checker checker2 chess clip colormat cone cube curve depthcue disk dof dofnot double drawf feedback fog fogindex font light linelist lines list list2 maplight material mipmap model movelight nurbs pickdepth pickline picksquare plane planet planetup polys robot sccolorlight scene scenebamb sceneflat select simple smooth sphere stencil stroke surface tea teaambient teapots texgen texturesurf trim xfont