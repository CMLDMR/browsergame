#include "MapContainer.h"
#include "Bootstrap/inlinestyle.h"

#include <Wt/WEvent.h>
#include "Logger.h"

using namespace Wt;

MapContainer::MapContainer()
{

    setAttributeValue( Style::style , Style::background::url("ground.jpg") + Style::background::size::contain );

    setWidth( 1024 );
    setHeight( 1024 );

    std::cout << "dsfasdf\n";

    mouseMoved().connect([=]( const WMouseEvent &event){
        LOG_DEBUG("{} {}" , event.widget().x , event.widget().y );
    });
}
