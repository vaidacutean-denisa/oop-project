#include "../headers/Enemy.h"

#include <cmath>
#include <memory>

Enemy::Enemy(float health_, float enemySpeed_, const sf::Vector2f& enemyPosition_, float attackCooldown_)
    : health(health_), enemySpeed(enemySpeed_), enemyPosition(enemyPosition_), attackCooldown(attackCooldown_), distanceScalingFactor(0),
      hitboxScalingFactor(0)
{
    // enemySprite.setTexture(texture_);
    enemySprite.setPosition(enemyPosition_);
	enemySprite.setOrigin(enemySprite.getLocalBounds().width / 2.f, enemySprite.getLocalBounds().height / 2.f);

	attackClock.restart();
}

Enemy::Enemy(const Enemy& other) : health(other.health), enemySpeed(other.enemySpeed), enemyPosition(other.enemyPosition),
	  attackCooldown(other.attackCooldown), distanceScalingFactor(other.distanceScalingFactor),
	  hitboxScalingFactor(other.hitboxScalingFactor) {}

Enemy& Enemy::operator=(const Enemy& other) {
    if (this != &other) {
        health = other.health;
        enemySpeed = other.enemySpeed;
        enemyPosition = other.enemyPosition;
    	enemySprite = other.enemySprite;
    	attackClock = other.attackClock;
    	attackCooldown = other.attackCooldown;
    	distanceScalingFactor = other.distanceScalingFactor;
    	hitboxScalingFactor = other.hitboxScalingFactor
    }
    return *this;
}

Enemy::~Enemy() {
    // std::cout << "One step closer to survival.. (destructor enemy)\n";
}

void Enemy::drawEnemies(sf::RenderWindow& window) const {
    drawImplementation(window);
}

void Enemy::followPlayer(const sf::Vector2f& playerCenter, const sf::Vector2u& windowSize, const sf::Vector2f& playerSize) {
	sf::Vector2f currentPosition = getPosition();

	sf::Vector2f enemyCenter = {
		currentPosition.x + getSize().x / 2.f,
		currentPosition.y + getSize().y / 2.f
	};

	float dx = playerCenter.x - enemyCenter.x;
	float dy = playerCenter.y - enemyCenter.y;

	float distanceToPlayer = std::sqrt(dx * dx + dy * dy);

	if (distanceToPlayer != 0) {                                                // normalizarea vectorului
		dx /= distanceToPlayer;
		dy /= distanceToPlayer;
	}

	float minDistance = getMinDistanceToPlayer(playerSize);						// definita pentru a preveni suprapunerea inamicilor cu jucatorul

	if (distanceToPlayer < minDistance)
		return;                                                                 // daca inamicul e prea apoape de jucator, se opreste (ar trebui)

	float step = getSpeed();

	float newX = currentPosition.x + dx * step;
	float newY = currentPosition.y + dy * step;

	const auto windowWidth = static_cast<float>(windowSize.x);
	const auto windowHeight = static_cast<float>(windowSize.y);

	newX = std::clamp(newX, 0.f, windowWidth);
	newY = std::clamp(newY, 0.f, windowHeight);

	setPosition({newX, newY});
}

bool Enemy::checkCollision(const Enemy& other) const {
    const auto otherSprite = other.getSprite().getGlobalBounds();

    return getSprite().getGlobalBounds().intersects(otherSprite);
}

void Enemy::resolveCollision(const std::vector<std::unique_ptr<Enemy>>& enemies) {
    for (const auto& other : enemies) {
        if (other.get() == this)
            continue;

        if (!checkCollision(*other))
            continue;

        sf::Vector2f positionEnemy1 = getPosition();
        sf::Vector2f positionEnemy2 = other->getPosition();

        sf::Vector2f direction = positionEnemy1 - positionEnemy2;
        const float dx = direction.x;
        const float dy = direction.y;

        const float length = std::sqrt(dx * dx + dy * dy);

        if (length == 0.f) {
            setPosition(positionEnemy1 + sf::Vector2f(1.f, 0.f));
            return;
        }

        direction /= length;
        constexpr float pushDistance = 0.3f;

        setPosition(positionEnemy1 + direction * pushDistance);
    }
}

void Enemy::takeDamage(float amount) {
    health -= amount;
}

bool Enemy::isDead() const {
    return health <= 0;
}

const sf::Vector2f& Enemy::getPosition() const {
    return enemySprite.getPosition();
}

const sf::Sprite& Enemy::getSprite() const {
    return enemySprite;
}

void Enemy::setTexture(const sf::Texture& texture) {
    enemySprite.setTexture(texture);
}

void Enemy::setPosition(const sf::Vector2f& enemyPosition_) {
    enemyPosition = enemyPosition_;
    enemySprite.setPosition(enemyPosition);
}

float Enemy::getSpeed() const {
    return enemySpeed;
}

sf::Vector2f Enemy::getSize() const {
	return enemySprite.getGlobalBounds().getSize();
}

float Enemy::getHitboxFactor() const {
	return hitboxScalingFactor;
}

std::ostream& operator<<(std::ostream& os, const Enemy& enemy) {
	os << "Enemy - health = " << enemy.health << '\n'
	   << "Speed = " << enemy.enemySpeed << '\n';
	return os;
}