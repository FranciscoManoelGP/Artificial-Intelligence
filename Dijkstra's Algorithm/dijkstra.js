const graph = {
  start: {A: 5, B: 2},
  A: {C: 4, D: 2},
  B: {A: 8, D: 7},
  C: {D: 6, goal: 3},
  D: {goal: 1},
  goal: {}
};

function lowestCostNode(costs, processed) {
  return Object.keys(costs).reduce(function(lowest, node) {
    if (lowest === null || costs[node] < costs[lowest]) {
      if (!processed.includes(node)) {
        lowest = node;
      }
    }
    return lowest;
  }, null);
}

function dijkstra(graph) {
  // track lowest cost to reach each node
  var costs = Object.assign({goal: Infinity}, graph.start);

  // track paths
  var parents = {goal: null};
  for (var child in graph.start) {
    parents[child] = 'start';
  }

  // track nodes that have already been processed
  var processed = [];

  var node = lowestCostNode(costs, processed);

  while (node) {
    var cost = costs[node];
    var children = graph[node];
    for (var n in children) {
      var newCost = cost + children[n];
      if (!costs[n]) {
        costs[n] = newCost;
        parents[n] = node;
      }
      if (costs[n] > newCost) {
        costs[n] = newCost;
        parents[n] = node;
      }
    }
    processed.push(node);
    node = lowestCostNode(costs, processed);
  }

  var optimalPath = ['goal'];
  var parent = parents.goal;
  while (parent) {
    optimalPath.push(parent);
    parent = parents[parent];
  }
  optimalPath.reverse();

  var results = {
    distance: costs.goal,
    path: optimalPath
  };

  return results;
}

console.log(dijkstra(graph));