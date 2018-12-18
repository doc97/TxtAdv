function funcA()
    io.write("Hello from funcA()!\n")
end

function funcB(a, b)
    io.write(string.format("%d + %d = %d", a, b, a+b))
end