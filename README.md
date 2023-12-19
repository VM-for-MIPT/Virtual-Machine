# Virtual-Machine

For building this project, type:
```bash
cmake -DCMAKE_BUILD_TYPE=Release -B build/
make -C build/ -j8
```

For running interpreter gtests from `build` directory, type:
```bash
make interpreter_gtests
```

For running quadratic equation with coefficients entered by you from `build` directory, you should use
```bash
make run_quadratic
```