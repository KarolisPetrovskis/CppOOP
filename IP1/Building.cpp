#include <string>
#include <sstream>
#include <stdexcept>
#include <cassert>
#include <iostream>
#include <vector>
#include <ctime>

namespace Utils
{
    template <typename T>
    bool isPositive(T value)
    {
        return value > 0;
    }
    int getCurrentYear()
    {
        std::time_t t = std::time(nullptr);
        std::tm *now = std::localtime(&t);
        return now->tm_year + 1900;
    }
    bool isFutureYear(int year)
    {
        const int currentYear = getCurrentYear();
        return year > currentYear;
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
    Building(std::string address, int yearBuilt, double landArea)
        : Building(address, yearBuilt, landArea, 1)
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
        if (!address.empty())
            m_address = address;
        else
            throw std::invalid_argument("Address cannot be an empty string");
    }

    void setFloors(int floors)
    {
        if (Utils::isPositive(floors))
            m_floors = floors;
        else
            throw std::invalid_argument("Floors must be a positive number.");
    }

    void setYearBuilt(int yearBuilt)
    {
        if (Utils::isPositive(yearBuilt) && !Utils::isFutureYear(yearBuilt))
            m_yearBuilt = yearBuilt;
        else
            throw std::invalid_argument("Year built must be a positive number and not in the future.");
    }

    void setLandArea(double landArea)
    {
        if (Utils::isPositive(landArea))
            m_landArea = landArea;
        else
            throw std::invalid_argument("Land area must be a positive number.");
    }

    long long getId() const
    {
        return m_id;
    }

    std::string getAddress() const
    {
        return m_address;
    }

    int getFloors() const
    {
        return m_floors;
    }

    int getYearBuilt() const
    {
        return m_yearBuilt;
    }

    double getLandArea() const
    {
        return m_landArea;
    }

    static int getBuildingCount()
    {
        return s_buildingCount;
    }

    std::string toString() const
    {
        std::stringstream ss;
        ss << getId() << " " << getYearBuilt() << " " << getLandArea() << " " << getFloors() << " " << getAddress();
        return ss.str();
    }
};

int main()
{
    try
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
                Building building(address, 0, landArea, floors);
                assert(false);
            }
            catch (std::invalid_argument &e)
            {
                assert(std::string(e.what()) == "Year built must be a positive number and not in the future.");
            }

            try
            {
                Building building(address, Utils::getCurrentYear() + 1, landArea, floors);
                assert(false);
            }
            catch (std::invalid_argument &e)
            {
                assert(std::string(e.what()) == "Year built must be a positive number and not in the future.");
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

            try
            {
                Building building(address, yearBuilt, landArea, floors);
                building.setYearBuilt(0);
                assert(false);
            }
            catch (std::invalid_argument &e)
            {
                assert(std::string(e.what()) == "Year built must be a positive number and not in the future.");
            }

            try
            {
                Building building(address, yearBuilt, landArea, floors);
                building.setYearBuilt(Utils::getCurrentYear() + 1);
                assert(false);
            }
            catch (std::invalid_argument &e)
            {
                assert(std::string(e.what()) == "Year built must be a positive number and not in the future.");
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

            assert(Building::getBuildingCount() == 0);
            try
            {
                for (int i = 0; i < 5; ++i)
                {
                    buildings.push_back(new Building(address, yearBuilt, landArea, floors));
                    assert(Building::getBuildingCount() == i + 1);
                }
                for (int i = 5; i > 0; --i)
                {
                    delete buildings.back();
                    buildings.pop_back();
                    assert(Building::getBuildingCount() == i - 1);
                }
            }
            catch (...)
            {
                for (Building *building : buildings)
                {
                    delete building;
                }
                throw;
            }
            std::cout << "Test 5 passed\n\n";
        }
    }
    catch (...)
    {
        std::cout << "An error occurred" << std::endl;
    }
    assert(Building::getBuildingCount() == 0);
    return 0;
}