#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkGlyph3D.h>
#include <vtkCellArray.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPointData.h>
#include <vtkCubeSource.h>
#include <vtkDoubleArray.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPoints> points =
   vtkSmartPointer<vtkPoints>::New();
  vtkSmartPointer<vtkDoubleArray> radius =
   vtkSmartPointer<vtkDoubleArray>::New();

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
  cubeSource.Get()->SetBounds(0,20,0,20,0,20);
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
}


