#include "dalele.h"

void Dalele::particle_Generator( MAP_BOUNDS map_boundai){ //daleliu generacija paduodant F masyva

   INT idx=1; // reikia keisti gali buti klaida
    vtkSmartPointer<vtkPoints> points =
         vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkDoubleArray> radius =
         vtkSmartPointer<vtkDoubleArray>::New();

     REAL4 tempDalele;
    for(INT i=0;i<V.size();i++){
     tempDalele=V[i];
     //cout << tempDalele << endl;
     points->InsertNextPoint(tempDalele[0],tempDalele[1], tempDalele[2]);
     radius->InsertNextTuple1(tempDalele[3]);
    }
    Skirstinys sk;


   vtkSmartPointer<vtkPolyData> polydata =
      vtkSmartPointer<vtkPolyData>::New();
    polydata->SetPoints(points);
  polydata->GetPointData()->SetScalars(radius);
    vtkSmartPointer<vtkPolyData> glyph =
      vtkSmartPointer<vtkPolyData>::New();

    // Create anything you want here, we will use a cube for the demo.
    vtkSmartPointer<vtkSphereSource> SphereSource =
        vtkSmartPointer<vtkSphereSource>::New();
    SphereSource->SetRadius(sk.NextSpindulys());
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
REAL4 MAP_BOUNDS_MIN=map_boundai.getMAP_BOUNDS_MIN();
REAL4 MAP_BOUNDS_MAX=map_boundai.getMAP_BOUNDS_MAX();

    vtkSmartPointer<vtkCubeSource> cubeSource =
      vtkSmartPointer<vtkCubeSource>::New();
    cubeSource.Get()->SetBounds(MAP_BOUNDS_MIN[0], MAP_BOUNDS_MAX[0],
            MAP_BOUNDS_MIN[1], MAP_BOUNDS_MAX[1], MAP_BOUNDS_MIN[2], MAP_BOUNDS_MAX[2]);
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

vector<REAL4> Dalele::getF() const
{
    return F;
}

void Dalele::setFvec(const REAL4 value)
{
    F.push_back(value);
}
void Dalele::setF(const vector<REAL4> &value)
{
    F = value;
}
vector<REAL4> Dalele::getV() const
{
    return V;
}

void Dalele::setV(const vector<REAL4> &value)
{
    V = value;
}




