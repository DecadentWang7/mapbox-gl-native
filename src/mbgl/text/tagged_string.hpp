#pragma once

#include <mbgl/text/glyph.hpp>
#include <mbgl/text/bidi.hpp>

namespace mbgl {

struct SectionOptions {
    SectionOptions(double scale_, FontStackHash fontStackHash_)
        : scale(scale_), fontStackHash(fontStackHash_)
    {}
    
    double scale;
    FontStackHash fontStackHash;
};

struct TaggedString {
    TaggedString() = default;

    TaggedString(std::u16string text_, SectionOptions options)
        : styledText(std::move(text_),
                     std::vector<uint8_t>(text_.size(), 0)) {
        sections.push_back(std::move(options));
    }
    
    TaggedString(StyledText styledText_, std::vector<SectionOptions> sections_)
        : styledText(std::move(styledText_))
        , sections(std::move(sections_)) {
    }

    std::size_t length() const {
        return styledText.first.length();
    }
    
    std::size_t sectionCount() const {
        return sections.size();
    }
    
    bool empty() const {
        return styledText.first.empty();
    }
    
    const SectionOptions& getSection(std::size_t index) const {
        return sections.at(styledText.second.at(index));
    }
    
    char16_t getCharCodeAt(std::size_t index) const {
        return styledText.first[index];
    }
    
    const std::u16string& rawText() const {
        return styledText.first;
    }
    
    const StyledText& getStyledText() const {
        return styledText;
    }
    
    void addSection(const std::u16string& text, double scale, FontStackHash fontStack);
    const SectionOptions& sectionAt(std::size_t index) const {
        return sections.at(index);
    }
    
    const std::vector<SectionOptions>& getSections() const {
        return sections;
    }
    
    uint8_t getSectionIndex(std::size_t characterIndex) const {
        return styledText.second.at(characterIndex);
    }
    
    double getMaxScale() const;
    void trim();
    
    void verticalizePunctuation();
   
private:
    StyledText styledText;
    std::vector<SectionOptions> sections;
};

} // namespace mbgl