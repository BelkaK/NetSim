#include "package.hpp"

class Package
{
public:
    Package()
    {
        // konstruktor domyślny (ma przyznawać najmniejszy możliwy numer id)
        // najpierw szuka w freed_IDs.
    }
    Package(ElementID id)
    {
        // przydziela ID takie jak id (jeżeli id jest wolne)
    }
    Package(Package &&)
    {
        // konstruktor NIE kopiujący!!!!!
        // konstruktor przesuwający
        // ustala parametry nowego obiektu na stary
        // i "USUWA" stary obiekt (ustawia id starego na np. -1)
    }
    Package &operator=(Package &&other)
    {
        if (this == &other)
            return *this;
        id = other.id;
        other.id = -1;
    }
    ElementID get_id() const
    {
        return id;
    }
    ~Package()
    {
        // ma dodać id usuwanego obiektu do freed_IDs
        // i usunąć je z assigned_IDs
    }

private:
    ElementID id;
    static std::list<ElementID> assigned_IDs;
    static std::list<ElementID> freed_IDs;
};
