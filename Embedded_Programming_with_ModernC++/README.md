# References
[is_integral](//https://en.cppreference.com/w/cpp/types/is_integral)
[is_arithmetic](//https://en.cppreference.com/w/cpp/types/is_arithmetic)
[Moving Resources](https://towardsdatascience.com/c-basics-moving-resources-4bd58bc5e6c8)


# Build
## Safety-Critical Systems
```bash
g++ Embedded_Programming_with_ModernC++/safety_critical_systems.cpp -o safety_critical_systems ; ./safety_critical_systems ; rm -rf ./safety_critical_systems
```

## High Performance
```bash
g++ Embedded_Programming_with_ModernC++/high_performance.cpp -o high_performance ; ./high_performance ; rm -rf ./high_performance
```
## Reduced Resources
```bash
g++ Embedded_Programming_with_ModernC++/reduced_resources.cpp -o reduced ; ./reduced ; rm -rf ./reduced
```


## Several Tasks Simultaneously
```bash
g++ Embedded_Programming_with_ModernC++/several_tasks_simultaneously.cpp -lpthread -o several ; ./several ; rm -rf ./several
```