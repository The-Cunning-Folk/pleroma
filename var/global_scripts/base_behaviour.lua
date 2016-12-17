Behaviour = {}

--called on spawn
function Behaviour:start(self)
end

--called upon activation
function Behaviour:wake(self)
end

--called every loop
function Behaviour:update(self)
end

--called when the object is made inactive
function  Behaviour:sleep(self)
end

-- called upon deactivation
function Behaviour:finish(self)
end