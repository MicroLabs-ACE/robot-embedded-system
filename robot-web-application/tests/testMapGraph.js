import { ok } from "assert";
import _ from "underscore";
import { MapGraph } from "../src/utils/mapGraph.js";

let map = new MapGraph(2, 2);
const twoByTwoGraph = {
  "0-0": { "1-0": 4, "0-1": 3, "1-1": 5 },
  "0-1": { "1-0": 5, "0-0": 3, "1-1": 4 },
  "1-0": { "0-0": 4, "0-1": 5, "1-1": 3 },
  "1-1": { "1-0": 3, "0-1": 4, "0-0": 5 },
};

console.log("2 by 2 Graph - Is Equal?", _.isEqual(map.graph, twoByTwoGraph));
map.removeNode("0-0");

const twoByTwoGraphRemovedNode = {
  "0-1": { "1-0": 5, "1-1": 4 },
  "1-0": { "0-1": 5, "1-1": 3 },
  "1-1": { "1-0": 3, "0-1": 4 },
};

console.log(
  "2 by 2 Graph - Removed Edge:",
  _.isEqual(map.graph, twoByTwoGraphRemovedNode),
);

map.addNode("0-0", true);
console.log("2 by 2 Graph - Is Equal?", _.isEqual(map.graph, twoByTwoGraph));

map = new MapGraph(3, 3);
console.log("Djikstra:", map.dijkstra("0-0", "2-2"));
console.log("DFS:", map.dfs("0-0"));
console.log("BFS:", map.bfs("0-0"));
