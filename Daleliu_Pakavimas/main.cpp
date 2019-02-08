#include "includes.h"
#include "geometry.h"
#include "dalele.h"
#include "grid_count.h"
#include "map_bounds.h"
int main(int, char *[])
{



    Dalele particle;
    Geometry geometrija;
    MAP_BOUNDS boundai;
    GRID_COUNT gridas;
    particle.DalelesDuomenuApibrezimas();
    boundai.MAP_DUOMENYS(boundai.MAP_BOUNDS_MIN,boundai.MAP_BOUNDS_MAX,boundai.CELLSIZE, boundai.Nx, boundai.Ny, boundai.Nz);
    geometrija.skirstinioFormavimas(particle);
    particle.Triju_DaleliuGeneracija(particle.min, particle.max, boundai, particle);
    gridas.GRIDAS(boundai.MAP_BOUNDS_MIN, boundai.MAP_BOUNDS_MAX, boundai.CELLSIZE, boundai.Nx, boundai.Ny, boundai.Nz, particle.F ,gridas.SUFORMUOTAS_GRIDAS);
    map<INT, INT>::iterator itr;
    for (itr = gridas.SUFORMUOTAS_GRIDAS.begin(); itr != gridas.SUFORMUOTAS_GRIDAS.end(); ++itr) {
            cout << '\t' << itr->first
                 << '\t' << itr->second << '\n';
        }
    //cout << gridas.SUFORMUOTAS_GRIDAS.size() << endl;
   // for(auto const& pair: gridas.SUFORMUOTAS_GRIDAS){
      //  cout << pair.first << " " << pair.second <<  " " << particle.F.size() << endl;
   // }
    //map<INT, INT> gquiz1;
     //map<INT, INT>::iterator itr;
    //gquiz1.insert(pair<INT, INT>(1, 40));
    /*for (itr = gquiz1.begin(); itr != gquiz1.end(); ++itr) {
            cout << '\t' << itr->first
                 << '\t' << itr->second << '\n';
        }
*/
/*
  vtkSmartPointer<vtkPoints> points =
   vtkSmartPointer<vtkPoints>::New();
  vtkSmartPointer<vtkDoubleArray> radius =
   vtkSmartPointer<vtkDoubleArray>::New();

  points->InsertNextPoint(1,1,1);
  radius->InsertNextTuple1(1);
  points->InsertNextPoint(3,1,1);
  radius->InsertNextTuple1(1);
  points->InsertNextPoint(1.2,3.2,1);
  radius->InsertNextTuple1(1.2);
  points->InsertNextPoint(3,3.2,1);
  radius->InsertNextTuple1(1);




  for(int i=0;i<19;i++){
      for(int j=0;j<19;j++){
          for(int z=0;z<19;z++){
  points->InsertNextPoint(i+1,j+1,z+1);
  radius->InsertNextTuple1(1);
}
      }
  }

  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
polydata->GetPointData()->SetScalars(radius);
  vtkSmartPointer<vtkPolyData> glyph =
    vtkSmartPointer<vtkPolyData>::New();

  // Create anything you want here, we will use a cube for the demo.
  vtkSmartPointer<vtkSphereSource> SphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
  SphereSource->SetRadius(1);
  SphereSource->SetPhiResolution(4);
  SphereSource->SetThetaResolution(4);
  SphereSource.Get()->GetCenter();

  vtkSmartPointer<vtkGlyph3D> glyph3D =
    vtkSmartPointer<vtkGlyph3D>::New();
  glyph3D->SetColorModeToColorByScalar();
  glyph3D->SetScaleFactor(1);
#if VTK_MAJOR_VERSION <= 5
  glyph3D->SetSource(SphereSource->GetOutput());
  glyph3D->SetInput(polydata);
#else
  glyph3D->SetSourceConnection(SphereSource->GetOutputPort());
  glyph3D->SetInputData(polydata);
#endif
  glyph3D->Update();


  vtkSmartPointer<vtkCubeSource> cubeSource =
    vtkSmartPointer<vtkCubeSource>::New();
  cubeSource.Get()->SetBounds(0,1,0,1,0,1);
  //cubeSource.GetProperty()->SetOpacity(.4);
  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(glyph3D->GetOutputPort());


  vtkSmartPointer<vtkPolyDataMapper> Cubemapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  Cubemapper->SetInputConnection(cubeSource->GetOutputPort());

  vtkSmartPointer<vtkActor> Cubeactor =
    vtkSmartPointer<vtkActor>::New();
  Cubeactor->GetProperty()->SetOpacity(.2);
  Cubeactor->SetMapper(Cubemapper);

  vtkSmartPointer<vtkActor>Glyphactor =
    vtkSmartPointer<vtkActor>::New();
    Glyphactor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(Cubeactor);
  renderer->AddActor(Glyphactor);
  renderer->SetBackground(0, 0, 0); // Background color green

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
 */
}


