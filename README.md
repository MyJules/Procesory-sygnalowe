# Procesory-sygnalowe

# Clone:

git clone --recursive

# Build:

mkdir build 

cd build 

cmake ..

make

# Adding new Effects

Every effect must inherit IEffect interface. Processing logic is inside processConsoleParam, this method get's ConsoleParam stucture from Console parser and decides what to do with it. To add new audio effect you need to create new class, inherit it from IEffect. Every effect has it's own set of parameters, so we must process them in the first place. First of all we must add it to ConsoleParam as a optional type, for audio paramteres it's necessary to define operator << and operator >> so parser can read them. When creating Effects, you should use dedicated method

Example:
```
auto echo = createEffect<Echo>(params.echoParams.value());
wav = echo->process(wav, wavFormat);
```
