from ugdk.ugdk_graphic import Node, Modifier, Drawable
from ugdk.ugdk_drawable import TexturedRectangle
from ugdk.ugdk_math import Vector2D
from ugdk.ugdk_base import Color, Engine_reference
from Radio import SOUND_PATH
from random import randint


def window_size():
    return Engine_reference().video_manager().video_size()

#   Functions or attributes marked with ### means they're part of the 
#   C++ ScriptEntity interface

class BasicEntity:
    def __init__(self, x, y, texture_name, radius, life):
        self.radius = radius  ###
        self.size = Vector2D(self.radius*2, self.radius*2)
        texture_obj = Engine_reference().resource_manager().texture_container().Load(texture_name)
        self.shape = TexturedRectangle( texture_obj, self.size )
        self.shape.set_hotspot(Drawable.CENTER)
        self.shape.thisown = 0
        self.node = Node( self.shape )   ###
        self.node.modifier().set_offset( Vector2D(x,y) )
        self.node.thisown = 0
        self.new_objects = []  ###
        self.is_destroyed = False ###
        self.type = str(self.__class__)  ###
        self.velocity = Vector2D(0.0, 0.0)
        self.last_velocity = None
        self.last_dt = 0.0
        self.life = life
        self.max_life = life
        self.hit_sounds = ["hit1.wav", "hit2.wav", "hit3.wav", "hit4.wav"]

	def GetPos(self):
		return self.node.modifier().offset()
		
	def HandleMapBoundaries(self, pos):
        max = window_size()
        # checking for horizontal map boundaries
        if pos.get_x() < 0.0:
            pos.set_x( max.get_x() + pos.get_x() )
        if pos.get_x() > max.get_x():
            pos.set_x( pos.get_x() - max.get_x() )
        # checking for vertical map boundaries
        if pos.get_y() < 0.0:
            pos.set_y( max.get_y() + pos.get_y() )
        if pos.get_y() > max.get_y():
            pos.set_y( pos.get_y() - max.get_y() )
            
    def Update(self, dt): ###
        self.UpdatePosition(dt)

    def UpdatePosition(self, dt):
        pos = self.GetPos()
        pos = pos + (self.velocity * dt)
        self.last_velocity = self.velocity
        self.last_dt = dt
		self.HandleMapBoundaries(pos)
        self.node.modifier().set_offset(pos)

    def GetDamage(self, obj_type):
        # returns the amount of damage this object causes on collision with given obj_type
        print self.type, " GetDamage NOT IMPLEMENTED"

    def TakeDamage(self, damage):
        self.life -= damage
        if damage > 0:
            sound_name = self.hit_sounds[ randint(0, len(self.hit_sounds)-1) ]
            sound = Engine_reference().audio_manager().LoadSample(SOUND_PATH + sound_name)
            sound.Play()
        if self.life > self.max_life:
            self.life = self.max_life
        if self.life <= 0:
            self.is_destroyed = True

    def ApplyVelocity(self, v):
        self.velocity = self.velocity + v

    def HandleCollision(self, target): ###
        print self.type, " HandleCollision NOT IMPLEMENTED"
        
    def ApplyCollisionRollback(self):
        pos = self.GetPos()
        pos = pos + (self.last_velocity * -self.last_dt)
		self.HandleMapBoundaries(pos)
		pos = pos + (self.velocity * self.last_dt)
		self.HandleMapBoundaries(pos)
		self.node.modifier().set_offset(pos)
		self.last_velocity = self.velocity
		

