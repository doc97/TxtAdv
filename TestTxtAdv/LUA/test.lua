function matches_true(str)
    return true
end

function matches_false(str)
    return false
end

function matches_key(str)
    return str == "key"
end

function action_handle(str)
    handle()
end

function action_lib_handle(str)
    test.handle()
end