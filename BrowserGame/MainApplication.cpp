#include "MainApplication.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>

#include "MapContainer.h"

MainApplication::MainApplication(const Wt::WEnvironment &env)
    :Wt::WApplication( env )
{
    root()->addNew<MapContainer>();
}
