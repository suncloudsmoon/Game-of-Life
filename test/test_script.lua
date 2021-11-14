
function start()
	state = GetEntityStateAt(3, 3)
	print("Grid State: " .. tostring(state))
end

function MousePressed(x, y)
	print("X is " .. x .. ", Y is " .. y)
	SetEntityStateAt(x, y, not GetEntityStateAt(x,y))
	return true
end

function ButtonPressed(state)
	print("State is " .. tostring(state))
end
