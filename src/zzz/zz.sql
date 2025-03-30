WITH RECURSIVE min_cost_path AS (
    SELECT 
		point1 AS city, 
		point2 AS next_city, 
		cost, 
		1 AS level, 
		point1 AS start_city, 
		ARRAY[point1] AS visited_cities
    FROM nodes
    WHERE point1 = 'a'
    UNION ALL
    SELECT 
		n.point1 AS city, 
		n.point2 AS next_city, 
		n.cost + mcp.cost, 
		mcp.level + 1, mcp.start_city, 
		mcp.visited_cities || n.point1
    FROM nodes n
    	JOIN min_cost_path mcp ON n.point1 = mcp.next_city
    WHERE NOT n.point2 = ANY(mcp.visited_cities)
)

SELECT *
FROM min_cost_path JOIN nodes AS p 
	ON min_cost_path.next_city = p.point1
WHERE level = 3
ORDER BY 1 DESC;