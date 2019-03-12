#include "dalele.h"



void Dalele::DalelesDuomenuApibrezimas()
{
    min=2;
    max=5;
    daleliuKiekis=100;
}
void Dalele::Triju_DaleliuGeneracija(MAP_BOUNDS map_boundai, REAL_ARRAY Distribution, REAL4_ARRAY F){

    INT idx=Distribution[0];
    vtkSmartPointer<vtkPoints> points =
         vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkDoubleArray> radius =
         vtkSmartPointer<vtkDoubleArray>::New();

     REAL4 tempDalele;
    for(INT i=0;i<F.size();i++){
     tempDalele=F[i];
     points->InsertNextPoint(tempDalele[0],tempDalele[1], tempDalele[2]);
     radius->InsertNextTuple1(tempDalele[3]);
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
    SphereSource->SetRadius(Distribution[idx]);
    SphereSource->SetPhiResolution(30);
    SphereSource->SetThetaResolution(30);
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
    cubeSource.Get()->SetBounds(map_boundai.MAP_BOUNDS_MIN[0], map_boundai.MAP_BOUNDS_MAX[0],
            map_boundai.MAP_BOUNDS_MIN[1], map_boundai.MAP_BOUNDS_MAX[1], map_boundai.MAP_BOUNDS_MIN[2] ,map_boundai.MAP_BOUNDS_MAX[2]);
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

  //  renderer->AddActor(Cubeactor);
    renderer->AddActor(Glyphactor);
    renderer->SetBackground(255, 255, 255); // Background color green

    renderWindow->Render();
    renderWindowInteractor->Start();


}
