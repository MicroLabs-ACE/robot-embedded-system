class Graph {
  constructor(length, width) {
    this.graph = {};
    this.generateGraph(length, width);
  }

  generateGraph(length, width) {
    this.length = length;
    this.width = width;

    for (let i = 0; i < this.length; i++)
      for (let j = 0; j < this.width; j++) {
        const nodes = {
          north: [i, j - 1],
          northEast: [i + 1, j - 1],
          east: [i + 1, j],
          southEast: [i + 1, j + 1],
          south: [i, j + 1],
          southWest: [i - 1, j + 1],
          west: [i - 1, j],
          northWest: [i - 1, j - 1],
        };

        for (const [node, coordinates] of Object.entries(nodes)) {
          const [x, y] = coordinates;
          var horizontalCondition = x >= 0 && x < this.length;
          var verticalCondition = y >= 0 && y < this.width;

          if (horizontalCondition && verticalCondition) {
            if (node === "north" || node === "south")
              this.addEdge(`${i}${j}`, `${x}${y}`, 10);
            else if (node === "west" || node === "east")
              this.addEdge(`${i}-${j}`, `${x}-${y}`, 10);
            else this.addEdge(`${i}-${j}`, `${x}-${y}`, 14);
          }
        }
      }
  }

  doesNodeExist(node) {
    return this.graph.hasOwnProperty(node);
  }

  addEdge(src, dst, weight) {
    if (!this.doesNodeExist(src)) {
      this.graph[src] = { [dst]: weight };
    } else {
      this.graph[src][dst] = weight;
    }

    if (!this.doesNodeExist(dst)) {
      this.graph[dst] = {};
    }
  }

  getDistance(src, dst) {
    return this.graph[src][dst];
  }

  getDirection(src, dst) {
    const [x0, y0] = src.split("-");
    const [x1, y1] = dst.split("-");

    const dx = Number(x1) - Number(x0);
    const dy = Number(y1) - Number(y0);

    let direction;
    if (dx === 0 && dy === 1) direction = 0;
    else if (dx === 1 && dy === 1) direction = 45;
    else if (dx === 1 && dy === 0) direction = 90;
    else if (dx === 1 && dy === -1) direction = 135;
    else if (dx === 0 && dy === -1) direction = 180;
    else if (dx === -1 && dy === -1) direction = 225;
    else if (dx === -1 && dy === 0) direction = 270;
    else if (dx === -1 && dy === 1) direction = 315;

    return direction;
  }

  dijkstra(start, end) {
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
      (node) => node !== start
    );
    const costs = {};
    const parents = {};
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
  }

  bfs(start) {
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
  }
}

export default function dijkstra_computation(length, width, start, end) {
  const graph = new Graph(length, width);
  return graph.dijkstra(start, end);
}

