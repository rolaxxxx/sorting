#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkActor.h>
#include <vtkCubeSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataSourceWidget.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
int main(int, char *[])
{
    // Create a cube.
      vtkSmartPointer<vtkCubeSource> cubeSource =
        vtkSmartPointer<vtkCubeSource>::New();
      cubeSource.Get()->SetBounds(0,1,0,1,0,1);

      //cubeSource.Get()->SetXLength(200);
      //cubeSource.Get()->SetYLength(100);
      //cubeSource.Get()->SetZLength(50);
      cout << cubeSource.Get()->GetXLength() << " " << cubeSource.Get()->GetYLength() << " " << cubeSource.Get()->GetZLength() << endl;

      // Create a mapper and actor.
      vtkSmartPointer<vtkPolyDataMapper> mapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
      mapper->SetInputConnection(cubeSource->GetOutputPort());

      vtkSmartPointer<vtkActor> actor =
        vtkSmartPointer<vtkActor>::New();
      actor->SetMapper(mapper);
        actor->GetProperty()->SetColor(1.0, 0.0, 0.0);
      // Create a renderer, render window, and interactor
      vtkSmartPointer<vtkRenderer> renderer =
        vtkSmartPointer<vtkRenderer>::New();
      vtkSmartPointer<vtkRenderWindow> renderWindow =
        vtkSmartPointer<vtkRenderWindow>::New();
      renderWindow->AddRenderer(renderer);
      vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
      renderWindowInteractor->SetRenderWindow(renderWindow);

      // Add the actors to the scene
      renderer->AddActor(actor);
      renderer->SetBackground(.3, .2, .1);

      // Render and interact
      renderWindow->Render();
      renderWindowInteractor->Start();

      return EXIT_SUCCESS;
}

