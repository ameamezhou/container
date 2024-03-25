#include <iostream>
#include <thread>
#include <vector>

void run()
{
    while (true) {

    }
}

int main()
{
    std::vector<std::thread> treads;
    for (int i = 0; i < std::thread::hardware_concurrency(); i++) {
        threads.emplace_back(run);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}

SELECT e.employee_id, e.last_name,
    CASE
        WHEN d.department_id = 1800 THEN 'Canada'
        ELSE 'USA'
    END AS location
FROM employees e
JOIN departments d ON e.department_id = d.department_id
JOIN locations l ON d.location_id = l.location_id;
