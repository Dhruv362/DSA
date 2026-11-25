template <typename Word>
concept BitsetWord = std::unsigned_integral<Word> &&
                     !std::same_as<std::remove_cv_t<Word>, bool> &&
                     std::same_as<Word, std::make_unsigned_t<Word>>;
template <BitsetWord Word, std::size_t extent = std::dynamic_extent>
struct BitsetView
{
    Word* words;
    static constexpr std::size_t capacity = extent;
};
template <BitsetWord Word>
struct BitsetView<Word, std::dynamic_extent>
{
    Word* words;
    std::size_t capacity;
};
template <bool value, typename Word>
[[nodiscard, gnu::always_inline]] constexpr Word assign_bits(
    Word word,
    Word mask) noexcept
{
    if constexpr (value)
    {
        return static_cast<Word>(word | mask);
    }
    else
    {
        return static_cast<Word>(word & ~mask);
    }
}
template <bool value, BitsetWord Word, std::size_t extent>
    requires(!std::is_const_v<Word>)
[[gnu::always_inline]] constexpr void bsv_fill(
    BitsetView<Word, extent> bits) noexcept
{
    constexpr auto width = sizeof(Word) * 8;
    constexpr auto max_word = static_cast<Word>(~Word{});
    const auto full_words = bits.capacity / width;
    const auto tail = bits.capacity % width;
    for (std::size_t i = 0; i != full_words; ++i)
    {
        bits.words[i] = value ? max_word : Word{};
    }
    if (tail)
    {
        const Word mask = static_cast<Word>(max_word >> (width - tail));
        auto& word = bits.words[full_words];
        word = assign_bits<value>(word, mask);
    }
}
template <BitsetWord Word, std::size_t extent>
[[nodiscard, gnu::always_inline]] constexpr bool bsv_get(
    BitsetView<Word, extent> bits,
    std::size_t index) noexcept
{
    constexpr auto width = sizeof(Word) * 8;
    return (bits.words[index / width] >> (index % width)) & 1;
}
template <bool value, BitsetWord Word, std::size_t extent>
    requires(!std::is_const_v<Word>)
[[gnu::always_inline]] constexpr Word bsv_set_if(
    BitsetView<Word, extent> bits,
    std::size_t index,
    bool condition) noexcept
{
    constexpr auto width = sizeof(Word) * 8;
    auto& word = bits.words[index / width];
    const Word mask = static_cast<Word>(Word{condition} << (index % width));
    word = assign_bits<value>(word, mask);
    return word;
}
template <bool value, BitsetWord Word, std::size_t extent>
    requires(!std::is_const_v<Word>)
[[gnu::always_inline]] constexpr void bsv_set(
    BitsetView<Word, extent> bits,
    std::size_t index) noexcept
{
    bsv_set_if<value>(bits, index, true);
}
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;
template <BitsetWord Word>
[[nodiscard, gnu::always_inline]] constexpr u32 ctl_zero(Word word) noexcept
{
    constexpr int width = sizeof(Word) * 8;
    return static_cast<u32>(__builtin_clzg(word, width));  // NOLINT
}
// First integer in [first, last) satisfying a false-then-true predicate, or
// last.
template <std::integral T, typename Predicate>
    requires(!std::same_as<T, bool>)
[[nodiscard]] constexpr T
lower_bound(T first, T last, Predicate&& predicate) noexcept(
    noexcept(static_cast<bool>(predicate(first))))
{
    using U = std::make_unsigned_t<T>;
    while (first != last)
    {
        const U distance =
            static_cast<U>(static_cast<U>(last) - static_cast<U>(first));
        const T mid = static_cast<T>(first + static_cast<T>(distance / 2));
        if (predicate(mid))
        {
            last = mid;
        }
        else
        {
            first = static_cast<T>(mid + 1);
        }
    }
    return first;
}
inline static constexpr auto iif =
    []<std::integral T> [[nodiscard, gnu::always_inline]] (
        bool c,
        T a,
        std::type_identity_t<T> b) noexcept -> T
{
    return b ^ ((a ^ b) & static_cast<T>(-c));
};
inline static constexpr auto max2 =
    []<typename T> [[gnu::always_inline, nodiscard]] (T a, T b) noexcept -> T
{
    if constexpr (std::integral<T>)
    {
        return iif(a < b, b, a);
    }
    else
    {
        return a < b ? b : a;
    }
};
inline static constexpr auto min2 =
    []<typename T> [[gnu::always_inline, nodiscard]] (T a, T b) noexcept -> T
{
    if constexpr (std::integral<T>)
    {
        return iif(b < a, b, a);
    }
    else
    {
        return b < a ? b : a;
    }
};
template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};
inline constexpr u32 kMOD = 1'000'000'007;
struct ModInt
{
    u32 value = 0;
};
[[gnu::always_inline]] constexpr ModInt& operator*=(
    ModInt& lhs,
    const ModInt& rhs) noexcept
{
    u64 v = rhs.value;
    v *= lhs.value;
    if (v >= kMOD) v %= kMOD;
    lhs.value = cast<u32>(v);
    return lhs;
}
[[nodiscard, gnu::always_inline]] constexpr ModInt operator*(
    ModInt lhs,
    const ModInt& rhs) noexcept
{
    lhs *= rhs;
    return lhs;
}
[[gnu::always_inline]] constexpr ModInt& operator-=(
    ModInt& lhs,
    const ModInt& rhs) noexcept
{
    lhs.value += kMOD & -u32{lhs.value < rhs.value};
    lhs.value -= rhs.value;
    return lhs;
}
[[nodiscard, gnu::always_inline]] constexpr ModInt operator-(
    ModInt lhs,
    const ModInt& rhs) noexcept
{
    lhs -= rhs;
    return lhs;
}
inline auto init = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 'c';
}();
struct GolfBoundsHashTable
{
    inline static u32 table[std::bit_ceil(2u * 100'000)];
    u32 capacity;
    [[gnu::always_inline]] explicit GolfBoundsHashTable(u32 windows) noexcept
        : capacity(1u << (32 - ctl_zero(2 * windows - 1)))
    {
        for (u32 i = 0; i != capacity; ++i) table[i] = 0;
    }
    struct InsertResult
    {
        bool first;
        bool second;
    };
    // Zero marks an empty slot. The high bit marks a repeated hash.
    [[nodiscard, gnu::always_inline]] InsertResult counting_insert(
        u32 hash) noexcept
    {
        u32 i = static_cast<u32>((u64{hash} * 0x9e3779b97f4a7c15ULL) >> 32);
        const u32 key = hash + 1;
        constexpr u32 repeated = 1u << 31;
        u32 entry = 0;
        do
        {
            i = (i + 1) & (capacity - 1);
            entry = table[i];
        } while (entry && (entry & ~repeated) != key);
        table[i] = key | (entry != 0 ? repeated : 0);
        return {entry == 0, entry == key};
    }
};
class Solution
{
public:
    inline static u32 prefix_hash[100'001];
    inline static constexpr u32 kBase = 911'382'323;
    inline static ModInt kBasePowers[100'001];
    inline static const bool precomputed = []
    {
        kBasePowers[0] = ModInt{1};
        for (u32 i = 1; i != 100'001; ++i)
        {
            kBasePowers[i] = kBasePowers[i - 1] * ModInt{kBase};
        }
        return true;
    }();
    static u32 next_hash(u32 prev_hash, u32 value)
    {
        return static_cast<u32>((u64{prev_hash} * kBase + value) % kMOD);
    }
    [[nodiscard, gnu::always_inline]] static u32 query_hash(
        u32 begin,
        u32 end) noexcept
    {
        const ModInt prefix =
            ModInt{prefix_hash[begin]} * kBasePowers[end - begin];
        return (ModInt{prefix_hash[end]} - prefix).value;
    }
    [[nodiscard, gnu::always_inline]] static bool exists_unique(
        u32 n,
        u32 k) noexcept
    {
        GolfBoundsHashTable hash_to_count{n - k + 1};
        u32 singletons = 0;
        for (u32 end = k; end != n + 1; ++end)
        {
            const auto [first, second] =
                hash_to_count.counting_insert(query_hash(end - k, end));
            singletons += first;
            singletons -= second;
        }
        return singletons != 0;
    }
    [[nodiscard]] static bool has_unique_value(const u32* a, u32 n) noexcept
    {
        constexpr u32 kWords = 100'000 / 32 + 1;
        using View = BitsetView<u32, kWords * 32>;
        View seen{prefix_hash}, repeated{prefix_hash + kWords};
        bsv_fill<false>(seen);
        bsv_fill<false>(repeated);
        for (u32 i = 0; i != n; ++i)
        {
            const u32 value = a[i];
            bsv_set<true>(bsv_get(seen, value) ? repeated : seen, value);
        }
        for (u32 i = 0; i != kWords; ++i)
        {
            if (seen.words[i] & ~repeated.words[i]) return true;
        }
        return false;
    }
    [[nodiscard]] static bool is_middle_pair_unique(
        const u32* a,
        u32 n) noexcept
    {
        const u32 mid = n / 2;
        const u32 x = a[mid - 1], y = a[mid];
        for (u32 i = 1; i != n; ++i)
        {
            if (i != mid && a[i - 1] == x && a[i] == y) return false;
        }
        return true;
    }
    struct LengthBounds
    {
        u32 first;
        u32 upper;
    };
    [[nodiscard]] static LengthBounds unique_length_bounds(
        const u32* a,
        u32 n) noexcept
    {
        // The longest prefix of the reversed input that also ends elsewhere
        // determines the shortest unique suffix of the original input.
        prefix_hash[0] = 0;
        u32 longest = 0;
        for (u32 i = 1, matched = 0; i != n; ++i)
        {
            const u32 value = a[n - 1 - i];
            while (matched && value != a[n - 1 - matched])
            {
                matched = prefix_hash[matched - 1];
            }
            matched += (value == a[n - 1 - matched]);
            prefix_hash[i] = matched;
            if (matched > longest) longest = matched;
        }
        // For length >= period, windows match exactly when their starts
        // have the same phase. With at least 2 * period windows every
        // phase occurs twice, even for shorter lengths.
        const u32 period = n - prefix_hash[n - 1];
        const u32 first = n > 2 * period ? n - 2 * period + 2 : 2;
        const u32 upper = min2(longest + 1, max2(period, first));
        return {first, upper};
    }
    [[gnu::flatten, gnu::no_sanitize_address]]
    static u32 impl(const u32* a, const u32 n) noexcept
    {
        if (has_unique_value(a, n)) return 1;
        if (is_middle_pair_unique(a, n)) return 2;
        auto [first, upper] = unique_length_bounds(a, n);
        if (first == upper) return first;
        prefix_hash[0] = 0;
        for (u32 i = 0; i != n; ++i)
        {
            prefix_hash[i + 1] = next_hash(prefix_hash[i], a[i]);
        }
        if (upper - first > 32)
        {
            const u32 k = first + (32u - ctl_zero(upper - first));
            if (exists_unique(n, k))
            {
                upper = k;
            }
            else
            {
                first = k + 1;
            }
        }
        return lower_bound(
            first,
            upper,
            [n] [[gnu::always_inline]] (u32 k) noexcept
            { return exists_unique(n, k); });
    }
    static u32 smallestUniqueSubarray(std::vector<int>& nums)
    {
        const u32 n = nums.size() & ~u32{};
        const auto* a = reinterpret_cast<const u32*>(nums.data());
        return impl(a, n);
    }
};