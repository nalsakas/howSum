#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>

std::vector<std::vector<int>> howSum(int target, std::vector<int>& numbers, bool& result, std::shared_ptr<std::map<int, std::vector<std::vector<int>>>> cache = nullptr)
{
    if (cache == nullptr)   
        cache = std::make_shared<std::map<int, std::vector<std::vector<int>>>>();
    
    if (cache->count(target))
    {
        auto cachedResult = cache->at(target);
        if (cachedResult.size() && cachedResult[0].size())
            result = true;
        else
            result = false;
        return cachedResult;
    }

    if (target == 0)
    {
        result = true;
        return {{}};
    }

    if (target < 0)
    {
        result = false;
        return {{}};
    }
        
    std::vector<std::vector<int>> collect = {};
    for (int num : numbers)
    {
        auto result = false;
        int remainder = target - num;
        auto ret = howSum(remainder, numbers, result, cache);
        if (result)
        {
            for (auto& item : ret)
                item.push_back(num);

            collect.insert(collect.end(), ret.begin(), ret.end());
        }
    }

    if (collect.size() && collect[0].size())
        result = true;
    else
        result = false;


    (*cache)[target] = collect;

    return collect;
}

int main()
{
    
    std::vector<int> numbers = {3, 14};
    int target = 50;
    bool result = false;
    auto res = howSum(target, numbers, result);

    if (result)
    {
        for (auto& item : res)
        {
            std::cout << "[ ";
            for (auto num : item)
                std::cout << num << " ";
            std::cout << "]" << std::endl;
        }
    }
    else
    {
        std::cout << "[]" << std::endl;
    }
    return 0;
}
