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
        // przydziela ID takie jak id
    }
    Package(Package &&)
    {
        // konstruktor kopiujący
    }
    Package &operator=(Package &&other)
    {
        // nadpisanie operatora przypisywania
        // nie wiem czemu nie pytajcie mnie ;-;
        if (this == &other)
            return *this;
        id = other.id;
    }
    Package &operator=(const Package &other)
    {
        // funkcja dodana przeze mnie!!!
        // żeby działała metoda pop() w PackageQueue
        // do naprawy i usunięcia w przyszłości
        if (this == &other)
            return *this;
        id = other.id;
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