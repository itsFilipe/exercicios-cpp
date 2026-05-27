#ifndef _LIDAR_FILTER_
#define _LIDAR_FILTER_

#include <vector>
#include <memory>

class LidarFilter {
private:
    int minDistance;
    int maxDistance;
public:
    LidarFilter(int minDistance = 5, int maxDistance = 110);

    // O método pede posse absoluta do ponteiro, e ao fim, retorna a posse.
    std::unique_ptr<std::vector<int>> applyFilter(std::unique_ptr<std::vector<int>> rawData);
};

#endif
