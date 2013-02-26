package com.skoobalon.lander.components {
	import com.skoobalon.lander.game.GameConstants;
	import flash.display.Graphics;
	import flash.display.Shape;
	import flash.display.Sprite;
	import flash.geom.Point;
	import flash.text.TextField;
	
	/**
	 * @author Steven Wallace
	 */
	public class FireballSet extends Shape {
		
		private var _averageLife:Number;
		
		private var _ball:Vector.<Fireball>;
		
		public function FireballSet(/*numParticles:int, averageLife:Number*/) {
			var numParticles:int = 4096;
			_averageLife = 1.0;
			
			_ball = new Vector.<Fireball>(numParticles);
			for (var i:int = 0; i < numParticles; i++) {
				_ball[i] = new Fireball();
			}
		}
		
		public function add(strength:Number, position:Point, angle:Number, maxRadius:int, dt:Number):void {
			var added:int = 0;
			
			for (var i:int = 0; i < _ball.length; i++) {
				if (added >= strength * 1500 * dt) {
					return;
				}
				
				if (_ball[i].radius <= 0.25) {
					var ball:Fireball = _ball[i];
					
					// I have little idea what this voodoo is!  Gotta love making a faithful port... :P
					ball.angle = angle + ( -30 + Math.random() * 60);
					var color:Number = 64;
					
					ball.radius = ball.originalRadius = Math.min(
						maxRadius * 10 / strength, 
						Math.random() * maxRadius - Math.random() * int(maxRadius * 50 / strength + 1));
					
					ball.x = position.x - 5 + Math.random() * 10;
					ball.y = position.y - 5 + Math.random() * 10;
						
					ball.velocity = new Point(
						Math.cos(ball.angle * Math.PI / 180) * strength / 5,
						Math.sin(ball.angle * Math.PI / 180) * strength / 5);
					
					//_ball[i]
					added++;
				}
			}
		}
		
		public function update(dt:Number):void {
			graphics.clear();
			
			for (var i:int = 0; i < _ball.length; i++) {
				var ball:Fireball = _ball[i];
				
				if (ball.radius > 0.25) {
					ball.velocity.y -= 15 * GameConstants.GRAVITY * dt;
					ball.y += ball.velocity.y * dt * 10;
					ball.x += ball.velocity.x * dt * 10;
					ball.radius -= ball.originalRadius / (_averageLife * (0.25 + Math.random() * 1.5)) * dt;
					
					ball.color += (224 - 64) * _averageLife * dt;
					if (ball.color > 255) {
						ball.color = 255;
					}
					
					graphics.beginFill((ball.color << 16) | (ball.color << 8) | ball.color, 1);
					graphics.drawCircle(ball.x, ball.y, ball.radius);
					graphics.endFill();
					
				}
				
			}
		}
		
	}

}
