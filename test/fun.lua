
--[[
Notes:
mandatory function to be present in each script: start(), MousePressed(x, y) returning true (handling stuff myself)/false, ButtonPressed()
function avaiable: GetEntityStateAt(x, y), SetEntityStateAt(x, y), GetRows, GetColumns
--]]

local function GenerateCross(x, y)
    if x - 1 >= 0 then
        SetEntityStateAt(x - 1, y, not GetEntityStateAt(x - 1, y))
    end
    if x + 1 < GetRows() then
        SetEntityStateAt(x + 1, y, not GetEntityStateAt(x + 1, y))
    end
    if y - 1 >= 0 then
        SetEntityStateAt(x, y - 1, not GetEntityStateAt(x, y - 1))
    end
    if y + 1 < GetColumns() then
        SetEntityStateAt(x, y + 1, not GetEntityStateAt(x, y + 1))
    end
    return false
end

local function GenerateGlider(x, y)
    if x - 1 >= 0 then
        SetEntityStateAt(x - 1, y, false)
    end
    if x + 1 < GetRows() then
        SetEntityStateAt(x + 1, y, false)
    end
    if x + 1 < GetRows() and y - 1 >= 0 then
        SetEntityStateAt(x + 1, y - 1, false)
    end
    if y - 2 >= 0 then
        SetEntityStateAt(x, y - 2, false)
    end
    return false
end

function start()

end

function MousePressed(x, y)
    return GenerateGlider(x, y)
end

function ButtonPressed(state)

end

