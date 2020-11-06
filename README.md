# corona_graph

A simpler clone of [corona_graph](https://github.com/Abathargh/corona_graph) that I'm using to teach myself some practical C language/tools + the Python C API.

## Installation and Usage

You need libcurl, python3-dev and make to compile. I'm using python3.8 with matplotlib installed globally; you may need to modify the Makefile according to where your libraries are located.

```bash
make all
./corona_graph
```

will download the json dataset from the Civil Protection github and generate a graph named graph.png containing the growth of Covid-19 cases in the regions of Italy.