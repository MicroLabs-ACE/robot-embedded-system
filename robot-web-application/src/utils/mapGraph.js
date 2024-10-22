export class MapGraph {
  constructor(length, width) {
    if (length <= 2 || width <= 2) {
      console.log("Length and width must be greater than 2");
      return;
    }

    this.length = length;
    this.width = width;
    this.graph = {};
    this.generateGraph();
  }

  generateGraph() {
    for (let i = 0; i < this.length; i++)
      for (let j = 0; j < this.width; j++) {
        const node = `${i}-${j}`;
        this.addNode(node);
      }
  }

  getCoordinatesFromNode(node) {
    return node.split("-").map((value) => parseInt(value, 10));
  }

  doesNodeExist(node) {
    return this.graph.hasOwnProperty(node);
  }

  isNodeValid(node) {
    const [i, j] = this.getCoordinatesFromNode(node);
    return i >= 0 && i < this.length && j >= 0 && j < this.width;
  }

  addEdge(src, dst, weight) {
    if (!this.doesNodeExist(src)) {
      this.graph[src] = { [dst]: weight };
    } else {
      this.graph[src][dst] = weight;
    }
  }

  addNode(node, isReconnection = false) {
    const [i, j] = this.getCoordinatesFromNode(node);
    const connections = {
      north: [i, j - 1],
      northEast: [i + 1, j - 1],
      east: [i + 1, j],
      southEast: [i + 1, j + 1],
      south: [i, j + 1],
      southWest: [i - 1, j + 1],
      west: [i - 1, j],
      northWest: [i - 1, j - 1],
    };

    const src = `${i}-${j}`;
    for (const [node, coordinates] of Object.entries(connections)) {
      const [x, y] = coordinates;
      const dst = `${x}-${y}`;

      const horizontalCondition = x >= 0 && x < this.length;
      const verticalCondition = y >= 0 && y < this.width;
      if (horizontalCondition && verticalCondition) {
        if (node === "north" || node === "south") {
          this.addEdge(src, dst, 3);
          if (isReconnection) this.addEdge(dst, src, 3);
        } else if (node === "west" || node === "east") {
          this.addEdge(src, dst, 4);
          if (isReconnection) this.addEdge(dst, src, 4);
        } else {
          this.addEdge(src, dst, 5);
          if (isReconnection) this.addEdge(dst, src, 5);
        }
      }
    }
  }

  removeNode(nodeToRemove) {
    if (!this.isNodeValid(nodeToRemove)) {
      console.log("Invalid node");
      return;
    }
    if (!this.doesNodeExist(nodeToRemove)) {
      console.log("Node does not exist");
      return;
    }

    const connectedNodes = this.graph[nodeToRemove];
    delete this.graph[nodeToRemove];

    for (const node in connectedNodes) {
      if (this.graph[node]) {
        delete this.graph[node][nodeToRemove];
      }
    }
  }

  getDirection(src, dst) {
    const [x0, y0] = this.getCoordinatesFromNode(src);
    const [x1, y1] = this.getCoordinatesFromNode(dst);
    const dx = x1 - x0;
    const dy = y1 - y0;

    const directions = {
      "0,1": 0,
      "1,1": 45,
      "1,0": 90,
      "1,-1": 135,
      "0,-1": 180,
      "-1,-1": 225,
      "-1,0": 270,
      "-1,1": 315,
    };

    return directions[`${dx},${dy}`];
  }

  dijkstra(start, end) {
    if (!this.doesNodeExist(start)) {
      console.log("Start node does not exist");
      return [];
    }

    const findLowestCostNode = (costs, processed) => {
      let lowestCost = Infinity;
      let lowestCostNode = null;
      for (const node in costs) {
        const cost = costs[node];
        if (cost < lowestCost && !processed.includes(node)) {
          lowestCost = cost;
          lowestCostNode = node;
        }
      }
      return lowestCostNode;
    };

    const nodesExceptStart = Object.keys(this.graph).filter(
      (node) => node !== start,
    );
    const costs = {};
    const parents = { [start]: null };
    const processed = [];

    nodesExceptStart.forEach((node) => {
      costs[node] = Infinity;
      parents[node] = null;
    });

    const startNeighbors = Object.keys(this.graph[start]);
    startNeighbors.forEach((node) => {
      parents[node] = start;
      costs[node] = this.graph[start][node];
    });

    let currentNode = findLowestCostNode(costs, processed);
    while (currentNode !== null) {
      const cost = costs[currentNode];
      const neighbors = this.graph[currentNode];

      for (const n in neighbors) {
        const newCost = cost + neighbors[n];
        if (costs[n] > newCost) {
          costs[n] = newCost;
          parents[n] = currentNode;
        }
      }
      processed.push(currentNode);
      currentNode = findLowestCostNode(costs, processed);
    }

    let path = [end];
    let point = parents[end];
    while (point !== start) {
      path.unshift(point);
      point = parents[point];
    }
    path.unshift(start);
    return path;
  }

  dfs(start) {
    if (!this.doesNodeExist(start)) {
      console.log("Start node does not exist");
      return new Set();
    }

    const stack = [start];
    const visited = new Set();
    visited.add(start);

    while (stack.length > 0) {
      const currentNode = stack.pop();
      const neighbors = this.graph[currentNode];
      for (const neighbor in neighbors) {
        if (!visited.has(neighbor)) {
          stack.push(neighbor);
          visited.add(neighbor);
        }
      }
    }

    return visited;
  }

  bfs(start) {
    if (!this.doesNodeExist(start)) {
      console.log("Start node does not exist");
      return new Set();
    }

    const queue = [start];
    const visited = new Set();
    visited.add(start);

    while (queue.length > 0) {
      const currentNode = queue.shift();
      const neighbors = this.graph[currentNode];
      for (const neighbor in neighbors) {
        if (!visited.has(neighbor)) {
          queue.push(neighbor);
          visited.add(neighbor);
        }
      }
    }

    return visited;
  }
}
