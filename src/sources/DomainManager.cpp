// user-defined headers
#include <DomainManager.h>

//////////////////////////////////////////////////////
//		Constructor			    //
//////////////////////////////////////////////////////
DomainManager::DomainManager(Mesh *meshObj)
                             : meshObj_(meshObj)
                               
{
}

void DomainManager::getHeatSourceParameters()
{
    // nzx_ = &meshObj_->x_grid_;
}