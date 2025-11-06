

# Automata Visualization Project

## Overview

This project is designed to create an educational visualization tool for the different classes of automata learned in any theory of computation class. Ava Ginsberg and I have been planning this project for a while, and finally both have time to work on it. We hope to host this project online, and as such are focused heavily on optimization to let these machines run as effectively as possible in browser.

## Structure

In order to maximize efficiency, we chose to implement the backend for this project in C. Pointer arithmetic allows for easy processing of state machines, and the static nature of the machine definitions let us enforce good practices for memory safety without much extra overhead. In order to use our C code on a website, we're diving into WebAssembly (wasm). Compiling to Wasm lets us convert our C backend into something that can run in a browser without any extra steps. 

TODO: frontend information, file structure once more organized