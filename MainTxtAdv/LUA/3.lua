function matches(s)
    return true
end

function action(s)
    state:setStr("text", s)
    story:prev()
end