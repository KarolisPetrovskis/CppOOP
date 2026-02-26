#include <string>
#include <sstream>
#include <stdexcept>
#include <cassert>
#include <iostream>
#include <vector>

namespace Utils
{
    bool isPositive(int value)
    {
        return value > 0;
    }
    bool isPositive(double value)
    {
        return value > 0.0;
    }
}

class Building
{
private:
    inline static int s_buildingCount = 0;
    inline static int s_nextId = 0;

    const long long m_id = s_nextId++;
    std::string m_address;
    int m_floors;
    int m_yearBuilt;
    double m_landArea;

public:
    Building(std::string address, int yearBuilt, double landArea) : Building(address, yearBuilt, landArea, 1)
    {
    }

    Building(std::string address, int yearBuilt, double landArea, int floors)
    {
        setAddress(address);
        setYearBuilt(yearBuilt);
        setLandArea(landArea);
        setFloors(floors);
        ++s_buildingCount;
    }

    ~Building()
    {
        --s_buildingCount;
    }

    void setAddress(std::string address)
    {
        if (address.empty())
            throw std::invalid_argument("Address cannot be an empty string");
        m_address = address;
    }

    void setFloors(int floors)
    {
        if (!Utils::isPositive(floors))
            throw std::invalid_argument("Floors must be a positive number.");
        m_floors = floors;
    }

    void setYearBuilt(int year)
    {
        m_yearBuilt = year;
    }

    void setLandArea(double landArea)
    {
        if (!Utils::isPositive(landArea))
            throw std::invalid_argument("Land area must be a positive number.");
        m_landArea = landArea;
    }

    long long getId()
    {
        return m_id;
    }

    std::string getAddress()
    {
        return m_address;
    }

    int getFloors()
    {
        return m_floors;
    }

    int getYearBuilt()
    {
        return m_yearBuilt;
    }

    double getLandArea()
    {
        return m_landArea;
    }

    static int getBuildingCount()
    {
        return s_buildingCount;
    }

    std::string toString()
    {
        std::stringstream ss;
        ss << getId() << " " << getYearBuilt() << " " << getLandArea() << " " << getFloors() << " " << getAddress();
        return ss.str();
    }
};

int main()
{
    const std::string address = "Street 1";
    const int yearBuilt = 1990;
    const double landArea = 500.25;
    const int floors = 5;

    std::cout << "Test 1 started" << std::endl;
    {
        Building building1(address, yearBuilt, landArea, floors);
        std::stringstream ss1;
        ss1 << 0 << " " << yearBuilt << " " << landArea << " " << floors << " " << address;
        const std::string buildingString1 = ss1.str();

        Building building2(address, yearBuilt, landArea);
        std::stringstream ss2;
        ss2 << 1 << " " << yearBuilt << " " << landArea << " " << 1 << " " << address;
        const std::string buildingString2 = ss2.str();

        assert(building1.getAddress() == address);
        assert(building1.getYearBuilt() == yearBuilt);
        assert(building1.getLandArea() == landArea);
        assert(building1.getFloors() == floors);
        assert(building1.toString() == buildingString1);
        assert(building1.getId() == 0);

        assert(building2.getAddress() == address);
        assert(building2.getYearBuilt() == yearBuilt);
        assert(building2.getLandArea() == landArea);
        assert(building2.getFloors() == 1);
        assert(building2.toString() == buildingString2);
        assert(building2.getId() == 1);

        std::cout << "Test 1 passed\n\n";
    }

    std::cout << "Test 2 started" << std::endl;
    {
        const std::string changedAddress = "Street 2";
        const int changedYearBuilt = 1995;
        const double changedLandArea = 5.5;
        const int changedFloors = 3;

        Building building(address, yearBuilt, landArea, floors);

        building.setAddress(changedAddress);
        building.setFloors(changedFloors);
        building.setLandArea(changedLandArea);
        building.setYearBuilt(changedYearBuilt);

        assert(building.getAddress() == changedAddress);
        assert(building.getFloors() == changedFloors);
        assert(building.getLandArea() == changedLandArea);
        assert(building.getYearBuilt() == changedYearBuilt);
        std::cout << "Test 2 passed\n\n";
    }

    std::cout << "Test 3 started" << std::endl;
    {
        try
        {
            Building building("", yearBuilt, landArea, floors);
            assert(false);
        }
        catch (std::invalid_argument &e)
        {
            assert(std::string(e.what()) == "Address cannot be an empty string");
        }

        try
        {
            Building building(address, yearBuilt, landArea, 0);
            assert(false);
        }
        catch (std::invalid_argument &e)
        {
            assert(std::string(e.what()) == "Floors must be a positive number.");
        }

        try
        {
            Building building(address, yearBuilt, 0, floors);
            assert(false);
        }
        catch (std::invalid_argument &e)
        {
            assert(std::string(e.what()) == "Land area must be a positive number.");
        }

        try
        {
            Building building(address, yearBuilt, landArea, floors);
            building.setAddress("");
            assert(false);
        }
        catch (std::invalid_argument &e)
        {
            assert(std::string(e.what()) == "Address cannot be an empty string");
        }

        try
        {
            Building building(address, yearBuilt, landArea, floors);
            building.setFloors(0);
            assert(false);
        }
        catch (std::invalid_argument &e)
        {
            assert(std::string(e.what()) == "Floors must be a positive number.");
        }

        try
        {
            Building building(address, yearBuilt, landArea, floors);
            building.setLandArea(-1.5);
            assert(false);
        }
        catch (std::invalid_argument &e)
        {
            assert(std::string(e.what()) == "Land area must be a positive number.");
        }

        std::cout << "Test 3 passed\n\n";
    }

    std::cout << "Test 4 started" << std::endl;
    {
        Building building1(address, yearBuilt, landArea, floors);
        Building building2(address, yearBuilt, landArea);

        assert(building1.getId() < building2.getId());

        std::cout << "Test 4 passed\n\n";
    }

    std::cout << "Test 5 started" << std::endl;
    {

        std::vector<Building *> buildings;

        auto cleanupAndAbort = [&]()
        {
            for (auto b : buildings)
                delete b;
            buildings.clear();
            assert(false);
        };

        assert(Building::getBuildingCount() == 0);

        try
        {
            for (int i = 0; i < 5; ++i)
            {
                buildings.push_back(new Building(address, yearBuilt, landArea, floors));
                if (Building::getBuildingCount() != i + 1)
                    cleanupAndAbort();
            }
            for (int i = 5; i > 0; --i)
            {
                delete buildings.back();
                buildings.pop_back();
                if (Building::getBuildingCount() != i - 1)
                    cleanupAndAbort();
            }
        }
        catch (std::exception &e)
        {
            cleanupAndAbort();
        }
        std::cout << "Test 5 passed\n\n";
    }
    return 0;
}